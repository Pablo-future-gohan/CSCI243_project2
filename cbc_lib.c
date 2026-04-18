///this will encode and decode a message
///@author Daniel "Pablo" Popovich

#include "cbc_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BITS_PER_BYTE   8L
#define BYTES_PER_BLOCK sizeof(long)
#define BITS_PER_BLOCK   (BYTES_PER_BLOCK * BITS_PER_BYTE)
#define INPUT_SIZE   (24 * BYTES_PER_BLOCK)


static block64 key = 0x1234DeadBeefCafe; // each hex digit is 4 bits
static const block64 INITIALIZATION_VECTOR = 0x0L; // initial IV value



int encode(const char * destpath){
	char buffer[1000];

	//this makes sure it can open the file and reads the input from the user
	FILE * fp = NULL;
	fp = fopen(destpath, "wb");
	if(fp==NULL){
		fprintf(stderr, "%s: No such file or directory\n", destpath);
		fprintf(stderr, "FAILED\n");
		return EXIT_FAILURE;
	}

	if(fgets(buffer, sizeof(buffer), stdin)==NULL){
		fprintf(stderr, "%s: Permission denied\n", destpath);
		fprintf(stderr, "FAILED\n");
		return EXIT_FAILURE;
	}


	//this encodes the message and writes to the file
	int numBlocks;
	if(!(strlen(buffer)%8)){
		 numBlocks = (int) (strlen(buffer)/8);
	}
	else{
		 numBlocks = (int) (strlen(buffer)/8) +1;
	}
	block64 pIV = INITIALIZATION_VECTOR;

	block64 *cipher = cbc_encrypt(buffer, numBlocks, &pIV, key);
	fwrite(cipher, sizeof(block64), numBlocks, fp);

	fprintf(stderr, "ok\n");

	fclose(fp);
	free(cipher);

	return EXIT_SUCCESS;
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
	for(size_t i=0; i<count; i++){
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
	for(size_t i=0; i<count; i++){
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


///this turns the plaintext byte sequence into a string with a nul bute at the end
///@param txt: the plaintext byte
///@param data the character array to be filled
static void block64_to_string( block64 txt, char * data){

	memcpy(data, &txt, 8);
	data[8]='\0';
}

///encryptes teh text using the pIV and key
///@param text: the text to be encrypted
///@param pIV: initialization vector or ciphertext input to the next stage
///@param key: key used to encrypt
///@return pointer to an array of block64
static block64 * cbc_encrypt( char * text, block64 * pIV, block64 key){


	int numBlocks;

	//figures out how many blocks there are so it can allocate the right amount
	if(!(strlen(text)%8)){
		 numBlocks = (int) (strlen(text)/8);
	}
	else{
		 numBlocks = (int) (strlen(text)/8) +1;
	}
	block64 * blockArray = (block64 *) malloc(numBlocks * sizeof(block64));


	//this loops and encrypts it
	for(int i=0; i<numBlocks; i++){

		
		block64 b=0;
		char * startPos=text + (i*8);

		if(i!=numBlocks-1){
			memcpy(&b, startPos, 8);
		} else{
			//if the text isn't a multiple of 8 bytes
			if((strlen(text)%8)){
				memcpy(&b, startPos, (strlen(text)%8));

			//if the text is a multiple of 8 bytes	
			} else{
				memcpy(&b, startPos, 8);
			}
		}

		b=b^*pIV;
		*pIV=block_cipher_encrypt(b, key);
		blockArray[i]=*pIV;



	}

	return blockArray;
}



///this decrypts a ciphertext
///@param ciphertext: what you want to decrypt
///@param count: the amount of blocks in the ciphertext
///@param pIV: the initialization vector or ciphertext block
///@param key: the key to xor with
///@return the text that was encrypted
static char * cbc_decrypt( block64 * ciphertext, size_t count, block64 * pIV, block64 key) {	

	char * t = (char *) malloc((count*8 +1)* sizeof(char));

	for(size_t i=0; i<count; i++){

		char * startPos=t + (i*8);

		block64 temp = ciphertext[i];
		block64 future_pIV=ciphertext[i];
		temp = block_cipher_decrypt(temp, key);
		temp = temp ^ *pIV;


		char tempString[9];
		block64_to_string(temp, tempString);
		

		memcpy(startPos, tempString, 8);

		*pIV=future_pIV;
	}
	t[count*8]='\0';


	return t;
}





