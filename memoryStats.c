#include <unistd.h>
#include <stdio.h>
#include <sys/statvfs.h>

int main(){
	struct statvfs buf;
	statvfs(".", &buf);
	float pages = sysconf(_SC_PHYS_PAGES);
	float psize = sysconf(_SC_PAGE_SIZE)/1000.0;
	float tpm = psize * pages/1000000;
	printf("Page size: %gKB\n", psize);
	printf("Total Page Size: %gGB\n", tpm);
	printf("Free: %ld\n", buf.f_bfree);
	printf("Free mounted file system space: %gGB\n", (buf.f_bfree-buf.f_bsize)/1000000000.0);
	printf("Free Inodes: %ld\n", buf.f_ffree);
}