#pragma once 

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>

#define CBUF_NO_DATA 0xff00


struct cbuf {
	uint8_t flags; 
	char *buffer; 
	int16_t size; 
	int16_t head, tail; 
}; 

#ifdef __cplusplus
extern "C" {
#endif

void cbuf_init(struct cbuf *self, char *buffer, uint16_t size); 

// allocate a dynamic buffer
void cbuf_alloc(struct cbuf *self, uint16_t size); 
void cbuf_free(struct cbuf *self); 

uint16_t cbuf_cnt(struct cbuf *self); 
uint16_t cbuf_space(struct cbuf *self); 
void cbuf_clear(struct cbuf *self); 
bool cbuf_empty(struct cbuf *self); 
bool cbuf_full(struct cbuf *self); 

//! deprecated
uint16_t cbuf_get(struct cbuf *self); 
uint8_t cbuf_put(struct cbuf *self, uint8_t data);
int cbuf_getn(struct cbuf *self, char *data, uint16_t size); 
int cbuf_putn(struct cbuf *self, const char *data, uint16_t size); 
//! --

int cbuf_write(struct cbuf *self, const char *data, int size); 
int cbuf_read(struct cbuf *self, char *data, int size); 

uint16_t cbuf_peek(struct cbuf *self, uint16_t pos);

#ifdef __cplusplus
}
#endif

