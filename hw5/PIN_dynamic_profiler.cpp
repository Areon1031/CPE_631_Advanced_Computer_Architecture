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

// Kyle Ray
// CPE 631 Advanced Computer Architecture
// Homework #5
// Problem 3
// February 26, 2018


// PIN Instrumentation Tool
// Dynamic Basic Blocks (Streams)
// Stream identified by (SA = Starting Address, SL = Stream Length)

// Output following:
// numStreams : The number of unique program streams (static)
// numStreamD : The number of program streams executed (dynamic)
// numMemRef  : The number of memory referencing instructions (dynamic)
// numIrefs   : The number of instructions executed (dynamic)
// maxStreamLen : The maximum stream length (the maximum number of instructions executed
//                in a sequence without a branch being taken
// avgStreamLen : The average stream length (calculated as numIref/numStreamD)

// Also output the streams
// stream id: (stream starting address, # instructions, # memory ref instructions), (# of occurrences) ; { (next stream id, frequency) }

#include <iostream>
#include <iomanip>
#include <fstream>
#include "pin.H"

#include <map>
#include <vector>
using namespace std;

ofstream OutFile;

// The running counts make them static to help the compiler optimize
static UINT64 numStreamS = 0;  // map size
static UINT64 numStreamD = 0;  // increment every time a stream is encountered
static UINT64 numMemRef = 0;   // Use existing 
static UINT64 numIref = 0;     // Use existing
static UINT64 maxStreamLen = 0; // Final Stat

// Control 
static bool firstInstruction = true;
static UINT64 currStream = 0;
static UINT64 currStreamLen = 0;

// Structure to hold information regarding a stream
struct stream_table_entry
{
  ADDRINT sa;                     // stream starting address
  UINT32  sl;                     // stream length
  UINT32  scount;                 // stream count -- how many times it has been executed
  UINT32  lscount;                // number of memory referencing instructions
  UINT32  nstream;                // number of unique next streams
  vector<UINT32> nstream_id;      // next stream id (index in the stream table)
  vector<UINT32> ncount;          // counter how many times the next stream is encountered
  stream_table_entry()
  {
    sa = 0x00000000;
    sl = 0;
    scount = 0;
    lscount = 0;
    nstream = 0;
  }
};

// Map of Streams
std::map<int, stream_table_entry> stream_table;

// ANALYSIS FUNCTIONS and HELPER FUNCTIONS
// Method to create a new stream
VOID CreateNewStream(ADDRINT sa, bool extensionStream)
{
  // Update current index pointer to the end of the list
  currStream = numStreamS;
  
  // Create a new stream and add it to the table
  if (!extensionStream)
  {
    stream_table.insert(std::pair<int, stream_table_entry>(currStream, stream_table_entry()));
    stream_table[currStream].sa = sa;
    stream_table[currStream].sl = 0;
    
    // Reset Control stream len
    currStreamLen = 0;
  }
  else
  {
    stream_table.insert(std::pair<int, stream_table_entry>(currStream, stream_table_entry()));
    stream_table[currStream].sa = sa;
    stream_table[currStream].sl = currStreamLen;
  }
  
  // Increment the stream count
  ++numStreamS;
}

// Method to find a stream by address
int FindStreamByAddress(const ADDRINT address)
{
  for (std::map<int, stream_table_entry>::iterator it = stream_table.begin(); it != stream_table.end(); ++it)
  {
    if (it->second.sa == address)
      return it->first;
  }
  
  // Return error 
  return -1;
}

// Method to update the overall instruction count
// Also, update the current stream data
VOID PIN_FAST_ANALYSIS_CALL docount(ADDRINT src) 
{ 
  // Check for the first instruction of the program
  if (firstInstruction)
  {
    // Add the first stream to the table
    CreateNewStream(src, false);
    
    // Update Control
    firstInstruction = false;
  }
  
  // Update the overall instruction count
  ++numIref;
  
  // Update the current stream data
  if (stream_table[currStream].scount == 0)
    stream_table[currStream].sl++;
    
  // Update the current stream length
  ++currStreamLen;
  
  // Has this stream been executed before?
  if (stream_table[currStream].scount > 0)
  {
    // Will this instruction go beyond the bounds of the existing stream?
    if (stream_table[currStream].sl == currStreamLen)
    {
      // If so, then create a new stream that will include execution from the existing stream
      CreateNewStream(stream_table[currStream].sa, true);
    }
  }
}

// Method to update the overall memory reference count
VOID PIN_FAST_ANALYSIS_CALL doCountMemReads() 
{
  // Update the overall mem ref count
  ++numMemRef; 
  
  // Update the current stream data
  if (stream_table[currStream].scount == 0)
    stream_table[currStream].lscount++;
}

// Method to update the overall memory reference count
VOID PIN_FAST_ANALYSIS_CALL doCountMemWrites() 
{ 
  // Update the overall mem ref count
  ++numMemRef; 
  
  // Update the current stream data
  if (stream_table[currStream].scount == 0)
    stream_table[currStream].lscount++;
}

// Method to check if a branch is taken
VOID CheckBranches(ADDRINT src, ADDRINT dst, INT32 taken)
{
  // Was the branch taken?
  if (taken)
  {
    // Check to see if target address is a new stream
    // If it is then create a new stream
    // If it isn't then set currStream
    int streamIdx = FindStreamByAddress(dst);
    
    // If the stream wasn't found
    if(streamIdx == -1)
    {
      // New Stream
      stream_table[currStream].scount++; // Update the current streams count
      stream_table[currStream].nstream_id.push_back(numStreamS);
      stream_table[currStream].ncount.push_back(1);
      
      // Create the new stream
      CreateNewStream(dst, false);
    }
    else
    {
      // Need to update the current streams jump count
      int updateIdx = 0;
      
      // Find the branches stream index in the current streams list
      bool entryExists = false;
      for (std::vector<UINT32>::iterator it = stream_table[currStream].nstream_id.begin(); it != stream_table[currStream].nstream_id.end(); ++it)
      {
        if (*it == (UINT32)streamIdx)
        {
          updateIdx = std::distance(stream_table[currStream].nstream_id.begin(), it);
          entryExists = true;
        }
      }
      
      // Update the current streams jump count for the target stream
      if (entryExists)
      {
        stream_table[currStream].ncount[updateIdx]++;
      }
      else
      {
        stream_table[currStream].nstream_id.push_back(streamIdx);
        stream_table[currStream].ncount.push_back(1);
      }
      
      // Update the current streams execution count
      stream_table[currStream].scount++;
      
      // Update the current stream pointer to that of the next
      currStream = streamIdx;
    }
    
    // Update Number of Streams Executed
    ++numStreamD;
  }
}

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{ 
  // Count the instruction towards the total
  INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount,
    IARG_ADDRINT,
    INS_Address(ins),
    IARG_FAST_ANALYSIS_CALL,
    IARG_END);
    
  
  // Check for branches
  //if (INS_IsBranchOrCall(ins))
  if (INS_IsBranch(ins))
  {
    // Check if the branch is taken
    // If branch is taken we need to check where it is going and find out if it's a new stream or not
    // Even if the branch isn't taken we need to check to see if it's an old stream that is continuing into a new stream
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)CheckBranches,
      IARG_INST_PTR,
      IARG_BRANCH_TARGET_ADDR,
      IARG_BRANCH_TAKEN,
      IARG_END);
  }
  else
  {
    // Grab the mem operands
    UINT32 memOperands = INS_MemoryOperandCount(ins);
  
    // Iterate over each memory operand of the instruction
    for (UINT32 memOp = 0; memOp < memOperands; ++memOp)
    {
      // Check for a read
      if (INS_MemoryOperandIsRead(ins, memOp))
      {
        //INS_InsertPredicatedCall(
        INS_InsertCall(
          ins, IPOINT_BEFORE, (AFUNPTR)doCountMemReads,
          IARG_FAST_ANALYSIS_CALL,
          IARG_END);
      }
  
      // Check for a read
      if (INS_MemoryOperandIsWritten(ins, memOp))
      {
        //INS_InsertPredicatedCall(
        INS_InsertCall(
          ins, IPOINT_BEFORE, (AFUNPTR)doCountMemWrites,
          IARG_FAST_ANALYSIS_CALL,
          IARG_END);
      }
    }
  }
}

// Method to output information to a file
VOID OutputStreamTable()
{
  // While outputting the stream table calculate any remaining stats
  for (std::map<int, stream_table_entry>::iterator it = stream_table.begin(); it != stream_table.end(); ++it)
  {
    OutFile << it->first << ":  ";
    OutFile << "(" << setw(18) << right << StringFromAddrint(it->second.sa) << ", " 
      << setw(5) << right << it->second.sl      << left << ", " 
      << setw(5) << right << it->second.lscount << left << "), " 
      << setw(2) << right << it->second.scount  << left << "; { ";
    for (UINT32 i = 0; i < it->second.nstream_id.size(); ++i)
    {
      OutFile << "(" << it->second.nstream_id[i] << ", " << it->second.ncount[i] << ") ";
    }
    OutFile << "}" << endl;
    
    // Get the stream length
    if (it->second.sl > maxStreamLen)
      maxStreamLen = it->second.sl;
  }
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
  "o", "PIN_dynamic_profile.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
  // Catch the final stream count
  stream_table[currStream].scount++;
  
  // Write to a file since cout and cerr maybe closed by the application
  OutFile.setf(ios::showbase);
  OutputStreamTable();
  OutFile << "Number of unique streams:           " << setw(15) << left << numStreamS         << endl;
  OutFile << "Number of program streams executed: " << setw(15) << left << numStreamD         << endl;
  OutFile << "Number of memory ref instructions:  " << setw(15) << left << numMemRef          << endl;
  OutFile << "Number of instructions executed:    " << setw(15) << left << numIref            << endl;
  OutFile << "Max Stream Length:                  " << setw(15) << left << maxStreamLen       << endl;
  OutFile << "Average Stream Length:              " << setw(15) << left << numIref/numStreamD << endl;
  OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
  cerr << "This tool profiles the application and provides statistics for dynamic streams" << endl;
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
