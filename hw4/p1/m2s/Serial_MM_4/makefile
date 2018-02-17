all:
	gcc -static -m32 -o mm_mult_serial mm_mult_serial.c

clean:
	rm mm_mult_serial *.txt *_Report

run:
	m2s --x86-sim detailed --ctx-config ctx_config --x86-config x86_config --mem-config mem_config --mem-report mm_Memory_Report 2>> SimResults.txt
