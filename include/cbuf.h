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
 * FILE ............... include/cbuf.h
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

