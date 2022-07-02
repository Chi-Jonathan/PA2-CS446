/*
Jonathan Chi/Chi-Jonathan
This code is meant to simulate the Linux "free" command
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/statvfs.h>

int main(){
	struct statvfs buf;
	statvfs(".", &buf);
	int pages = sysconf(_SC_PHYS_PAGES);
	float psize = sysconf(_SC_PAGE_SIZE)/1000.0;
	float tpm = psize * pages/10000000;
	printf("\n====Mounted File System (HD) information====\n");
	printf("Free Blocks: %ld\n", buf.f_bfree);
	printf("Total free mounted file system mem: %g\n", (buf.f_bfree*buf.f_bsize)/10000000000.0);
	printf("Free Inodes: %ld\n", buf.f_ffree);
	printf("\n====System RAM information====\n");
	printf("There are: %d pages available, each with %g kb\n", pages, psize);
	printf("Total Available Memory: %gGB\n\n", tpm);
	
	
}