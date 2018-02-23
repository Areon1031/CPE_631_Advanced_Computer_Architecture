// Pin calls this function every time a new basic block is encountered.
// It inserts a call to docount.
VOID Trace(TRACE trace, VOID *v)
{
    // Visit every basic block  in the trace
    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
    {
        UINT32 memReads = 0;
        UINT32 memWrites = 0;
        for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins))
        {
            if (INS_IsMemoryRead(ins)) ++memReads;
            if (INS_IsMemoryWrite(ins)) ++memWrites;
        }
        
        // Insert a call to docount for every bbl, passing the number of instructions.
        BBL_InsertCall(bbl, IPOINT_ANYWHERE, (AFUNPTR)docount, IARG_FAST_ANALYSIS_CALL,
                       //IARG_UINT32, BBL_NumIns(bbl), IARG_THREAD_ID, IARG_END);
                       IARG_UINT32, BBL_NumIns(bbl), IARG_UINT32, memReads, IARG_UINT32, memWrites, IARG_THREAD_ID, IARG_END);
        
    }
}

// This function is called before every block
//VOID PIN_FAST_ANALYSIS_CALL docount(UINT32 c, THREADID threadid)
VOID PIN_FAST_ANALYSIS_CALL docount(UINT32 c, UINT32 memReads, UINT32 memWrites, THREADID threadid)
{
    thread_data_t* tdata = get_tls(threadid);
    tdata->_count += c;
    tdata->_memReadCount += memReads;
    tdata->_memWriteCount += memWrites;
    tdata->_bblCount++;
}