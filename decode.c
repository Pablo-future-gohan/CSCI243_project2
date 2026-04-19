
///this will decode what's in the file the user wants decoded
///@author Daniel "Pablo" Popovich

#include "cbc_lib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){


	if(argc!=2){
		fprintf(stderr, "usage: decode file-name  # to standard input\n");
		return EXIT_FAILURE;
	}


	int status = decode(argv[1]);
	return status;
}
