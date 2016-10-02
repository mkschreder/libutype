#pragma once 

#include <inttypes.h>
#include <stdint.h>

#define CBUF_NO_DATA 0xff00

struct cbuf {
	char *buffer; 
	int16_t size; 
	int16_t head, tail; 
}; 

#ifdef __cplusplus
extern "C" {
#endif

void cbuf_init(struct cbuf *self, char *buffer, uint16_t size); 
uint16_t cbuf_cnt(struct cbuf *self); 
uint16_t cbuf_space(struct cbuf *self); 
void cbuf_clear(struct cbuf *self); 
uint8_t cbuf_empty(struct cbuf *self); 
uint8_t cbuf_full(struct cbuf *self); 
uint16_t cbuf_get(struct cbuf *self); 
uint8_t cbuf_put(struct cbuf *self, uint8_t data);
int cbuf_getn(struct cbuf *self, char *data, uint16_t size); 
int cbuf_putn(struct cbuf *self, const char *data, uint16_t size); 
uint16_t cbuf_peek(struct cbuf *self, uint16_t pos);

#ifdef __cplusplus
}
#endif

