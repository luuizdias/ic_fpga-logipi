#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "wishbone_wrapper.h"


int main(int argc, char ** argv){
	int fd, address ;
	unsigned short i ;
	int j;
	unsigned short writeVal ;
/*
	if(argc  < 2){
		printf("not enough arguments \n");
		return 0 ;
	}
*/
	for (j=0;j<2048;j++) {
		address = (int) 0x1000 + (j<<1); //strtol(argv[1], NULL, 0);//write
		writeVal = (unsigned short) j+1; //strtol(argv[2], NULL, 0);
		printf("Writing 0x%x @ 0x%x \n", writeVal, address);
		if(wishbone_write(&writeVal, 2, address) < 2){
			printf("Write error !");
		}
		
	}
for (j=0;j<2048;j++) {

	address = (int) 0x1000 + (j<<1); 
	unsigned short readVal ; //read
		wishbone_read(&readVal,2,address);
		printf("0x%x \n",readVal);

}

	
	close(fd);
	return 0 ;
}
