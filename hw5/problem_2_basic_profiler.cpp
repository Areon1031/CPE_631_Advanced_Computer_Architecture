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
#include <fstream>
#include "pin.H"

ofstream OutFile;

// The running count of instructions is kept here
// make it static to help the compiler optimize docount
static UINT64 icount = 0;
static UINT64 blockCount = 0;
static UINT64 memWriteCount = 0;
static UINT64 memReadCount = 0;

// This function is called before every instruction is executed
VOID PIN_FAST_ANALYSIS_CALL docount() { ++icount; }
VOID PIN_FAST_ANALYSIS_CALL doCountMemReads() { ++memReadCount; }
VOID PIN_FAST_ANALYSIS_CALL doCountMemWrites() { ++memWriteCount; }
VOID PIN_FAST_ANALYSIS_CALL block_count() { ++blockCount; }
   
// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
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
                IARG_FAST_ANALYSIS_CALL,
                IARG_END);
        }
        
        // Check for a read
        if (INS_MemoryOperandIsWritten(ins, memOp))
        {
            INS_InsertPredicatedCall(
            ins, IPOINT_BEFORE, (AFUNPTR)doCountMemWrites,
            IARG_FAST_ANALYSIS_CALL,
            IARG_END);
        }
    }
    
    // Check if instruction is branch
    if (INS_IsBranch(ins))
    {
      INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)block_count,
        IARG_FAST_ANALYSIS_CALL, IARG_END);
    }
    
    // Count the instruction towards the total
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount,
        IARG_FAST_ANALYSIS_CALL, IARG_END);
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "inscount_serial.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);
    OutFile << "Basic Blocks: " << blockCount << endl;
    OutFile << "Memory Reads: " << memReadCount << endl;
    OutFile << "Memory Writes: " << memWriteCount << endl;
    OutFile << "Total Instructions " << icount << endl;
    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
