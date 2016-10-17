#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cbuf.h"
#include "test-funcs.h"

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
	TEST(!cbuf_full(&buf)); 
	TEST(cbuf_space(&buf) == 15); 
	
	cbuf_clear(&buf); 

	const char *str = "01234567890123456789"; 
	int len = strlen(str);
	TEST(cbuf_write(&buf, str, strlen(str)) == 15); 
	TEST(cbuf_full(&buf)); 
	TEST(cbuf_space(&buf) == 0); 

	uint16_t cnt = cbuf_cnt(&buf); 
	printf("str %d: ", cnt); 
	for(int c = 0; c < cnt; c++){
		printf("%02x ", buf.buffer[c]); 
	} printf("\n"); 

	cbuf_clear(&buf); 
	// write 5 and then read 5 to advance the pointer from zero
	for(int c = 0; c < 5; c++){ cbuf_put(&buf, 'A'); cbuf_get(&buf); }
	// test double write
	cbuf_write(&buf, str, strlen(str)); 
	TEST(cbuf_full(&buf)); 
	TEST(cbuf_space(&buf) == 0); 

	cnt = cbuf_cnt(&buf); 
	printf("buf %d: ", cnt); 
	for(int c = 0; c < 16; c++){
		printf("%02x ", buf.buffer[c]); 
	} printf("\n"); 

	printf("read: "); 
	for(int c = 0; c < 15; c++){
		uint8_t ch = cbuf_get(&buf); 
		printf("%02x ", ch); 
		TEST(ch == str[c]); 
	} printf("\n"); 
	
	TEST(cbuf_empty(&buf)); 
	cbuf_clear(&buf); 
	
	// test read
	cbuf_put(&buf, 'A'); cbuf_get(&buf); // offset start one position to test double read 

	cbuf_write(&buf, str, strlen(str)); 
	TEST(cbuf_full(&buf)); 
	TEST(cbuf_space(&buf) == 0); 

	printf("buf: "); 
	for(int c = 0; c < 16; c++){
		printf("%02x ", buf.buffer[c]); 
	} printf("\n"); 

	char tmp[16], tmp2[16]; 
	memset(tmp2, 0xaa, sizeof(tmp2)); 
	TEST(cbuf_read(&buf, tmp, len) == 15); 	

	printf("read: "); 
	for(int c = 0; c < 16; c++){
		printf("%02x ", tmp[c]); 
	} printf("\n"); 

	TEST(memcmp(tmp, str, 15) == 0); 
	TEST(cbuf_cnt(&buf) == 0); 
	TEST(cbuf_empty(&buf)); 

	cbuf_clear(&buf); 
	TEST(cbuf_write(&buf, tmp, 16) == 15); 
	TEST(cbuf_read(&buf, tmp2, 16) == 15); 

	printf("tmp2: "); 
	for(int c = 0; c < 16; c++){
		printf("%02x ", tmp2[c]); 
	} printf("\n"); 

	TEST(memcmp(tmp, tmp2, 16) != 0); 
	TEST(memcmp(tmp, tmp2, 15) == 0); 

	return 0; 
}

