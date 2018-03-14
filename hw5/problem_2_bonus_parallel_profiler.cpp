/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2016 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <map>
#include "pin.H"

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "inscount_parallel.out", "specify output file name");

INT32 numThreads = 0;
ostream* OutFile = NULL;

// Force each thread's data to be in its own data cache line so that
// multiple threads do not contend for the same data cache line.
// This avoids the false sharing problem.
#define PADSIZE 56  // 64 byte line size: 64-8

// a running count of the instructions
class thread_data_t
{
  public:
    thread_data_t() : _count(0), _memReadCount(0), _memWriteCount(0), _bblCount(0) {}
    UINT64 _count;
    UINT64 _memReadCount;
    UINT64 _memWriteCount;
    UINT64 _bblCount;
    UINT8 _pad[PADSIZE];
};

// key for accessing TLS storage in the threads. initialized once in main()
static  TLS_KEY tls_key = INVALID_TLS_KEY;

// A map to store the data attached for each thread, and a lock to protect the map
std::map<THREADID, thread_data_t*> threads_data;
PIN_LOCK lock;

// function to access thread-specific data
thread_data_t* get_tls(THREADID threadid)
{
    thread_data_t* tdata = static_cast<thread_data_t*>(PIN_GetThreadData(tls_key, threadid));
    if (tdata == NULL)
    {
        cerr << "PIN_GetThreadData(" << tls_key << "," << threadid << ") Failed" << endl;
        PIN_ExitProcess(1);
    }

    PIN_GetLock(&lock, threadid);
    std::map<THREADID, thread_data_t*>::const_iterator it = threads_data.find(threadid);
    if ((it == threads_data.end()) || (it->second != tdata))
    {
        cerr << "PIN_GetThreadData(" << tls_key << "," << threadid << ") returned the wrong thread data" << endl;
        PIN_ExitProcess(1);
    }
    PIN_ReleaseLock(&lock);
    return tdata;
}

// This function is called before every block
VOID PIN_FAST_ANALYSIS_CALL docount(UINT32 c, THREADID threadid)
{
    thread_data_t* tdata = get_tls(threadid);
    tdata->_count += c;
    tdata->_bblCount++;
}

VOID PIN_FAST_ANALYSIS_CALL doCountMemReads(THREADID threadid)
{
    thread_data_t* tdata = get_tls(threadid);
    tdata->_memReadCount++;
}

VOID PIN_FAST_ANALYSIS_CALL doCountMemWrites(THREADID threadid)
{
    thread_data_t* tdata = get_tls(threadid);
    tdata->_memWriteCount++;
}

// This function tests operations with illegal TLS keys.
VOID TestIllegalTLSOPerations(THREADID threadid)
{
    static bool tested = false;
    if (tested)
        return;
    tested = true;

    // start with an invalid key
    TLS_KEY temp_tls_key = INVALID_TLS_KEY;
    // Try to get thread data - expected to fail
    if (PIN_GetThreadData(temp_tls_key, threadid) != NULL)
    {
        cerr << "PIN_GetThreadData(" << tls_key << "," << threadid << ") should have failed" << endl;
        PIN_ExitProcess(1);
    }
    // Create a key
    temp_tls_key = PIN_CreateThreadDataKey(NULL);
    if (temp_tls_key == INVALID_TLS_KEY)
    {
        cerr << "number of already allocated keys reached the MAX_CLIENT_TLS_KEYS limit" << endl;
        PIN_ExitProcess(1);
    }
    // Delete the key
    if (PIN_DeleteThreadDataKey(temp_tls_key) == FALSE)
    {
        cerr << "PIN_DeleteThreadDataKey failed" << endl;
        PIN_ExitProcess(1);
    }
    // Delete it again - expected to fail
    if (PIN_DeleteThreadDataKey(temp_tls_key) == TRUE)
    {
        cerr << "PIN_DeleteThreadDataKey should have failed" << endl;
        PIN_ExitProcess(1);
    }
    // Try to use the deleted key - expected to fail
    if (PIN_SetThreadData(temp_tls_key, new thread_data_t, threadid) != FALSE)
    {
        cerr << "PIN_SetThreadData should have failed" << endl;
        PIN_ExitProcess(1);
    }
}

VOID ThreadStart(THREADID threadid, CONTEXT *ctxt, INT32 flags, VOID *v)
{
    numThreads++;
    thread_data_t* tdata = new thread_data_t;
    if (PIN_SetThreadData(tls_key, tdata, threadid) == FALSE)
    {
        cerr << "PIN_SetThreadData failed" << endl;
        PIN_ExitProcess(1);
    }
    PIN_GetLock(&lock, threadid+1);
    threads_data.insert(std::make_pair(threadid, tdata));
    PIN_ReleaseLock(&lock);

    TestIllegalTLSOPerations(threadid);
}


// Pin calls this function every time a new basic block is encountered.
// It inserts a call to docount.
VOID Trace(TRACE trace, VOID *v)
{
    // Visit every basic block  in the trace
    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
    {   
        // Insert a call to docount for every bbl, passing the number of instructions.
        BBL_InsertCall(bbl, IPOINT_ANYWHERE, (AFUNPTR)docount, IARG_FAST_ANALYSIS_CALL,
                       IARG_UINT32, BBL_NumIns(bbl), IARG_THREAD_ID, IARG_END);
        
    }
}

VOID Instruction(INS ins, VOID* v)
{
    // Grab the mem operands
    UINT32 memOperands = INS_MemoryOperandCount(ins);
    
    // Iterate over each memory operand of the instruction
    for (UINT32 memOp = 0; memOp < memOperands; ++memOp)
    {
        // Check for a read
        if (INS_MemoryOperandIsRead(ins, memOp))
        {
            INS_InsertPredicatedCall(
                ins, IPOINT_BEFORE, (AFUNPTR)doCountMemReads,
                IARG_FAST_ANALYSIS_CALL, IARG_THREAD_ID,
                IARG_END);
        }
        
        // Check for a read
        if (INS_MemoryOperandIsWritten(ins, memOp))
        {
            INS_InsertPredicatedCall(
            ins, IPOINT_BEFORE, (AFUNPTR)doCountMemWrites,
            IARG_FAST_ANALYSIS_CALL, IARG_THREAD_ID,
            IARG_END);
        }
    }
}

// This function is called when the thread exits
VOID ThreadFini(THREADID threadIndex, const CONTEXT *ctxt, INT32 code, VOID *v)
{
    //thread_data_t* tdata = get_tls(threadIndex);
    //*OutFile << "Memory Reads[" << decstr(threadIndex) << "] = " << tdata->_memReadCount << endl;
    //*OutFile << "Memory Writes[" << decstr(threadIndex) << "] = " << tdata->_memWriteCount << endl;
    //*OutFile << "Basic Blocks[" << decstr(threadIndex) << "] = " << tdata->_bblCount << endl;
    //*OutFile << "Total Instructions[" << decstr(threadIndex) << "] = " << tdata->_count << endl;
}

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    *OutFile << "Total number of threads = " << numThreads << endl;
    thread_data_t* threads[numThreads];
    *OutFile << setw(20) << " ";
    for (int i = 0; i < numThreads; ++i)
    {
        threads[i] = get_tls(i);
	      char buffer[20];
	      sprintf(buffer, "Thread %d", i);
        *OutFile << setw(15) << left << buffer;
    }
    *OutFile << endl;
    
    *OutFile << setw(20) << left << "Basic Blocks: ";
    for (int j = 0; j < numThreads; ++j)
    {
        *OutFile << setw(15) << left << threads[j]->_bblCount;
    }
    *OutFile << endl;
    
    *OutFile << setw(20) << left << "Memory Reads: ";
    for (int j = 0; j < numThreads; ++j)
    {
        *OutFile << setw(15) << left << threads[j]->_memReadCount;
    }
    *OutFile << endl;
    
    *OutFile << setw(20) << left << "Memory Writes: ";
    for (int j = 0; j < numThreads; ++j)
    {
        *OutFile << setw(15) << left << threads[j]->_memWriteCount;
    }
    *OutFile << endl;
    
    *OutFile << setw(20) << left << "Total Instructions: ";
    for (int j = 0; j < numThreads; ++j)
    {
        *OutFile << setw(15) << left << threads[j]->_count;
    }
    *OutFile << endl;
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return 1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    PIN_InitSymbols();
    if (PIN_Init(argc, argv))
        return Usage();

    OutFile = KnobOutputFile.Value().empty() ? &cout : new std::ofstream(KnobOutputFile.Value().c_str());

    // Initialize the pin lock
    PIN_InitLock(&lock);

    // Obtain  a key for TLS storage.
    tls_key = PIN_CreateThreadDataKey(NULL);
    if (tls_key == INVALID_TLS_KEY)
    {
        cerr << "number of already allocated keys reached the MAX_CLIENT_TLS_KEYS limit" << endl;
        PIN_ExitProcess(1);
    }

    // Register ThreadStart to be called when a thread starts.
    PIN_AddThreadStartFunction(ThreadStart, NULL);

    // Register Fini to be called when thread exits.
    PIN_AddThreadFiniFunction(ThreadFini, NULL);

    // Register Fini to be called when the application exits.
    PIN_AddFiniFunction(Fini, NULL);

    // Register Trace to be called to instrument traces.
    TRACE_AddInstrumentFunction(Trace, NULL);
    
    // Register Instruction to be called to instrument instructions.
    INS_AddInstrumentFunction(Instruction, NULL);

    // Start the program, never returns
    PIN_StartProgram();

    return 1;
}
