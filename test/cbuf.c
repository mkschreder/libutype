#include "cbuf.h"
#include "test-funcs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	struct cbuf buf; 
	char data[16]; 
	cbuf_init(&buf, data, sizeof(data));  

	TEST(cbuf_get(&buf) == CBUF_NO_DATA); 

	TEST(cbuf_cnt(&buf) == 0); 
	TEST(cbuf_empty(&buf))
	TEST(cbuf_space(&buf) == 15); 

	for(int c = 0; c < 15; c++) cbuf_put(&buf, 'A'+c); 

	TEST(cbuf_cnt(&buf) == 15); 
	TEST(cbuf_full(&buf)); 
	TEST(cbuf_space(&buf) == 0); 

	TEST(cbuf_put(&buf, 'x') == 0); 

	for(int c = 0; c < 15; c++) TEST(cbuf_get(&buf) == 'A'+c); 

	TEST(cbuf_get(&buf) == CBUF_NO_DATA); 

	return 0; 
}

