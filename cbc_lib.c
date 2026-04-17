///this will encode and decode a message
///

#include "cbc_lib.h"
#include <stdlib.h>
#include <stdio.h>

#define BYTES_PER_BLOCK sizeof(long)


int encode(const char * destpath){
	return 1;
}

int decode (const char * sourcepath){
	return 1;
}

static block64 roll_right(block64 block, size_t count){
	return block;
}

static block64 roll_left(block64 block, size_t count){
	return block;
}


static block64 block_cipher_encrypt( block64 block, block64 key){
	return block;
}
static block64 block_cipher_decrypt( block64 block, block64 key){
	return block;
}
static void block64_to_string( block64 txt, char * data){
	printf("");
}

static block64 * cbc_encrypt( char * text, block64 * pIV, block64 key){
	return pIV;
}
static char * cbc_decrypt( block64 * ciphertext, size_t count, block64 * pIV, block64 key) {	
	char * t = "gofgbijbi";
	return t;
}





