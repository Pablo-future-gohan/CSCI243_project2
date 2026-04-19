///this will encode what a user types into the terminal and puts that into the file 
///@author Daniel "Pablo" Popovich

#include "cbc_lib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){


	if(argc!=2){
		fprintf(stderr, "usage: encode file-name  # from standard input\n");
		return EXIT_FAILURE;
	}


	int status = encode(argv[1]);

	return status;
}

