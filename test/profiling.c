#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cbuf.h"
#include "test-funcs.h"

void diff(const struct timespec *start, const struct timespec *end, struct timespec *out){
	if ((end->tv_nsec-start->tv_nsec)<0) {
		out->tv_sec = end->tv_sec-start->tv_sec-1;
		out->tv_nsec = 1000000000+end->tv_nsec-start->tv_nsec;
	} else {
		out->tv_sec = end->tv_sec-start->tv_sec;
		out->tv_nsec = end->tv_nsec-start->tv_nsec;
	}
}

int main(void){
	struct timespec time1, time2, out;
	int temp;
	struct cbuf buf; 
	cbuf_alloc(&buf, 256); 
	char data[256]; 
	for(int c = 0; c < sizeof(data); c++){
		data[c] = rand(); 
	}

	printf("cbuf_cnt(): %d\n", cbuf_cnt(&buf)); 
	printf("cbuf_space(): %d\n", cbuf_space(&buf)); 

	printf("cbuf_putn(%lu): ", sizeof(data)); 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	TEST(cbuf_putn(&buf, data, sizeof(data)) == (sizeof(data) - 1)); 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	diff(&time1, &time2, &out); 
	printf("%lu:%lu\n", out.tv_sec, out.tv_nsec);  

	printf("cbuf_write(%lu): ", sizeof(data)); 
	cbuf_clear(&buf); 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	TEST(cbuf_write(&buf, data, sizeof(data)) == (sizeof(data) - 1)); 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	diff(&time1, &time2, &out); 
	printf("%lu:%lu\n", out.tv_sec, out.tv_nsec);  

	cbuf_write(&buf, data, sizeof(data)); 	
	printf("cbuf_getn(%lu): ", sizeof(data)); 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	TEST(cbuf_getn(&buf, data, sizeof(data)) == (sizeof(data) - 1)); 	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	diff(&time1, &time2, &out); 
	printf("%lu:%lu\n", out.tv_sec, out.tv_nsec);  

	cbuf_write(&buf, data, sizeof(data)); 	
	printf("cbuf_read(%lu): ", sizeof(data)); 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	TEST(cbuf_read(&buf, data, sizeof(data)) == (sizeof(data) - 1));  	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	diff(&time1, &time2, &out); 
	printf("%lu:%lu\n", out.tv_sec, out.tv_nsec);  


	return 0;
}

