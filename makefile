all: fileSystemInfo memoryStats

fileSystemInfo: fileSystemInfo.c
	gcc -o fileSystemInfo fileSystemInfo.c

memoryStats: memoryStats.c
	gcc -o memoryStats memoryStats.c

clean:
	rm -f *.o fileSystemInfo memoryStats