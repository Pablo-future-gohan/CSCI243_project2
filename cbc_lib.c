///this will encode and decode a message
///@author Daniel "Pablo" Popovich

#include "cbc_lib.h"
#include <stdlib.h>
#include <stdio.h>


#define BITS_PER_BYTE   8L
#define BYTES_PER_BLOCK sizeof(long)
#define BITS_PER_BLOCK   (BYTES_PER_BLOCK * BITS_PER_BYTE)
#define INPUT_SIZE   (24 * BYTES_PER_BLOCK)



int encode(const char * destpath){
	return 1;
}

int decode (const char * sourcepath){
	return 1;
}

///this moves the bits to the right and moves the ones that fall off to the right
///@param block: the block to shift bits in
///@param count: the amount of bits to shift
///@return the new block
static block64 roll_right(block64 block, size_t count){

	//this loops count number of times
	//it finds the rightmost bit
	//shifts that bit back 63 positions
	//shifts the block right once
	//does a bit | between them to change block
	for(int i=0; i<count; i++){
		block64 rightBit = block & 1;
		rightBit = rightBit<<63;
		block = block>>1;
		block = (block | rightBit);

	}


	return block;
}


///this moves the bits to the right and moves the ones that fall off to the right
///@param block: the block to shift bits in
///@param count: the amount of bits to shift
///@return the new block
static block64 roll_left(block64 block, size_t count){

	//this loops count number of times
	//it finds the leftmost bit
	//shifts that bit forward 63 positions
	//shifts the block left once
	//does a bit | between them to change block
	for(int i=0; i<count; i++){
		block64 leftBit = (block >>63) & 1;
		block = block << 1;
		block = (block | leftBit);
	}

	return block;

}



//this encrypts a cipher using a key by left bit rolling first and then xor with key
//@param block: the block to encrypt
//@param key: the key to xor the cipher with
//@return: the encrypted cipher
static block64 block_cipher_encrypt( block64 block, block64 key){

	for(int i=0; i<4; i++){
		block = roll_left(block, 10);
		block = block ^ key;
	}


	return block;
}


//this decryptes a cipher using a key by xoring with the key and then right bit rolling
//@param block: the block to encrypt
//@param key: the key to xor the cipher with
//@return: the encrypted cipher
static block64 block_cipher_decrypt( block64 block, block64 key){
	
	for(int i=0; i<4; i++){
		block = block ^ key;
		block = roll_right(block, 10);
	}


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





