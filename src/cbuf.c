/** :ms-top-comment
 * +-------------------------------------------------------------------------------+
 * |                      ____                  _ _     _                          |
 * |                     / ___|_      _____  __| (_)___| |__                       |
 * |                     \___ \ \ /\ / / _ \/ _` | / __| '_ \                      |
 * |                      ___) \ V  V /  __/ (_| | \__ \ | | |                     |
 * |                     |____/ \_/\_/ \___|\__,_|_|___/_| |_|                     |
 * |                                                                               |
 * |               _____           _              _     _          _               |
 * |              | ____|_ __ ___ | |__   ___  __| | __| | ___  __| |              |
 * |              |  _| | '_ ` _ \| '_ \ / _ \/ _` |/ _` |/ _ \/ _` |              |
 * |              | |___| | | | | | |_) |  __/ (_| | (_| |  __/ (_| |              |
 * |              |_____|_| |_| |_|_.__/ \___|\__,_|\__,_|\___|\__,_|              |
 * |                                                                               |
 * |                       We design hardware and program it                       |
 * |                                                                               |
 * |               If you have software that needs to be developed or              |
 * |                      hardware that needs to be designed,                      |
 * |                               then get in touch!                              |
 * |                                                                               |
 * |                            info@swedishembedded.com                           |
 * +-------------------------------------------------------------------------------+
 *
 *                       This file is part of uType Library
 *
 * FILE ............... src/cbuf.c
 * AUTHOR ............. Martin K. Schröder
 * VERSION ............ Not tagged
 * DATE ............... 2019-05-29
 * GIT ................ https://github.com/mkschreder/libfirmware
 * WEBSITE ............ http://swedishembedded.com
 * LICENSE ............ Swedish Embedded Open Source License
 *
 *          Copyright (C) 2014-2019 Martin Schröder. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this text, in full, shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cbuf.h"

#define CBUF_FLAG_DYNAMIC 0x01

#define _cbuf_hmt(name) ((int16_t)(name)->head - (int16_t)(name)->tail)

static uint16_t _calc_size(uint16_t size){
	uint16_t bit = 0; 
	for(uint16_t c = 0; c < sizeof(size) * 8; c++){
		if(size & 1) bit = c; 
		size >>= 1; 
	}
	return (uint16_t)(1 << bit); // make sure we round down to power of two or just 1
}

void cbuf_init(struct cbuf *self, char *buffer, uint16_t size){
	self->head = self->tail = 0; 
	self->size = _calc_size(size); 
	self->buffer = buffer; 
}

void cbuf_alloc(struct cbuf *self, uint16_t size){
	self->head = self->tail = 0; 
	self->flags = CBUF_FLAG_DYNAMIC; 
	self->size = _calc_size(size); 
	self->buffer = calloc(self->size, 1); 
}

void cbuf_free(struct cbuf *self){
	if(!(self->flags & CBUF_FLAG_DYNAMIC)) return; 
	free(self->buffer); 
	self->flags = 0; 
	self->buffer = NULL; 
}

void cbuf_clear(struct cbuf *self){
	self->head = self->tail = 0; 
	memset(self->buffer, 0, self->size); 
}

uint16_t cbuf_cnt(struct cbuf *self){
	int16_t hmt = _cbuf_hmt(self); 
	return (hmt < 0)?(hmt + ((self)->size)):hmt; 
}

uint16_t cbuf_space(struct cbuf *self){
	return self->size - cbuf_cnt(self) - 1; 
}

bool cbuf_empty(struct cbuf *self){
	return self->head == self->tail; 
}

bool cbuf_full(struct cbuf *self){
	return ((self)->head == (((self)->tail - 1) & ((self)->size - 1))); 
}

uint8_t cbuf_put(struct cbuf *self, uint8_t data){
	uint16_t next_head = (self->head + 1) & (self->size - 1); 
	if(next_head != self->tail){
		self->buffer[self->head] = data; 
		self->head = next_head; 
		return 1; 
	} 
	return 0; 
}

uint16_t cbuf_get(struct cbuf *self){
	if(self->head != self->tail) {
		uint16_t c = self->buffer[self->tail]; 
		self->tail = (self->tail + 1) & (self->size - 1); 
		return c; 
	}
	return CBUF_NO_DATA; 
}

int cbuf_getn(struct cbuf *self, char *data, uint16_t size){
	uint16_t s; 
	for(s = 0; s < size; ++s){
		uint16_t ch = cbuf_get(self); 
		if(ch == CBUF_NO_DATA) break; 
		*data++ = ch; 
	}
	return s; 
}

int cbuf_putn(struct cbuf *self, const char *data, uint16_t size){
	uint16_t s = 0; 
	for(s = 0; s < size; ++s){
		if(!cbuf_put(self, *data)) break;  
		data++; 
	}
	return s; 
}

int cbuf_write(struct cbuf *self, const char *data, int size){
	if(size <= 0) return -EINVAL; 
	uint16_t space = cbuf_space(self); 
	if(size > space) size = space;  
	//printf("head: %d, space: %d, size: %d\n", self->head, space, self->size); 
	uint16_t next_head = (self->head + size) & (self->size - 1); 
	uint16_t next_head_one = (self->head + 1) & (self->size - 1); 
	if(next_head_one + size > (self->size - 0)){ // need two writes
		uint16_t rem = self->size - self->head; 
		//printf("double write: %d(%d), %d(%d)\n", self->head, rem, 0, size - rem); 
		memcpy(&self->buffer[self->head], data, rem); 
		memcpy(self->buffer, data + rem, size - rem); 
	} else {
		//printf("single write: %d(%d)\n", next_head_one, size); 
		memcpy(&self->buffer[self->head], data, size); 
	}
	self->head = next_head; 

	return size; 
}

int cbuf_read(struct cbuf *self, char *data, int size){
	if(size <= 0) return -EINVAL; 
	uint16_t cnt = cbuf_cnt(self); 
	if(size >= cnt) size = cnt;  
	//printf("tail: %d, cnt: %d, size: %d\n", self->tail, cnt, self->size); 
	uint16_t next_tail = (self->tail + size) & (self->size - 1); 
	if(self->tail + size > (self->size - 1)){ // need two reads
		uint16_t rem = self->size - self->tail; 
		//printf("double read: %d(%d), %d(%d)\n", self->tail, rem, 0, size - rem); 
		memcpy(data, &self->buffer[self->tail], rem); 
		memcpy(data + rem, self->buffer, size - rem); 
	} else {
		//printf("single read\n"); 
		memcpy(data, &self->buffer[self->tail], size); 
	}
	self->tail = next_tail; 
	return size; 
}

uint16_t cbuf_peek(struct cbuf *self, uint16_t pos){
	if(cbuf_cnt(self) >= pos) return CBUF_NO_DATA; 

	int16_t i = (self->tail + pos + 1) & (self->size - 1); 
	return self->buffer[i]; 
}
