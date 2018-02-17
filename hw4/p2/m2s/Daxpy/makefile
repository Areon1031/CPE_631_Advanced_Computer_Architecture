all:
	gcc -static -m32 -o daxpy daxpy.c
	gcc -static -m32 -o daxpy_2 daxpy_2.c
	gcc -static -m32 -o daxpy_4 daxpy_4.c
	gcc -static -m32 -o daxpy_8 daxpy_8.c
	gcc -static -m32 -o daxpy_16 daxpy_16.c
clean:
	rm daxpy daxpy_2 daxpy_4 daxpy_8 daxpy_16 *.txt *_Report*

run:
	m2s --x86-sim detailed --ctx-config ctx_config --x86-config x86_config --mem-config mem_config --mem-report mm_Memory_Report 2>> SimResults.txt
	m2s --x86-sim detailed --ctx-config ctx_config_2 --x86-config x86_config --mem-config mem_config --mem-report mm_Memory_Report_2 2>> SimResults.txt
	m2s --x86-sim detailed --ctx-config ctx_config_4 --x86-config x86_config --mem-config mem_config --mem-report mm_Memory_Report_4 2>> SimResults.txt
	m2s --x86-sim detailed --ctx-config ctx_config_8 --x86-config x86_config --mem-config mem_config --mem-report mm_Memory_Report_8 2>> SimResults.txt
	m2s --x86-sim detailed --ctx-config ctx_config_16 --x86-config x86_config --mem-config mem_config --mem-report mm_Memory_Report_16 2>> SimResults.txt
