
///this will decode what's in the file the user wants decoded
///@author Daniel "Pablo" Popovich

#include "cbc_lib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){


	if(argc!=2){
		fprintf(stderr, "usage: encode to-file-name");
		return EXIT_FAILURE;
	}


	int status = encode(argv[1]);
	return status;
}
