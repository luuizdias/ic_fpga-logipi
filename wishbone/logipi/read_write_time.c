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
	int fd,address ;
	unsigned short i ;
	int j, k;
	int bits = atoi(argv[1]);
	unsigned char *writeVal ;
	//logfile
	char text[15] = "logfile";
	strcat(text,argv[2]);
	strcat(text,".csv");	
	FILE *log;
	log = fopen(text,"a");
	
	//leitura de tempo
	struct timeval temp1,temp2;
	long elapsed_u_sec,elapsed_s_sec,elapsed_m_time,elapsed_u_time;


	if(bits%2 != 0 || bits > 2048){
		printf("not enough arguments \n");
		return 0 ;
	}

	fprintf(log,"%d,",bits);

	//printf("WRITE\n");
	writeVal = (unsigned char *) malloc(sizeof(unsigned short)*bits);
	for (j=0;j<bits;j++) { // write
		//address = (int) 0x1000 + (j<<1); //strtol(argv[1], NULL, 0);//write
		writeVal[j] = (unsigned char) j+1; //strtol(argv[2], NULL, 0);
		//printf("Writing 0x%x @ 0x%x \n", writeVal, address		
	}
	gettimeofday(&temp1,NULL);
	for(k=0;k<10; k++){
		wishbone_write(writeVal, bits, (int) 0x1000);
	}
	gettimeofday(&temp2,NULL);

	elapsed_u_time = ((temp2.tv_usec-temp1.tv_usec)+(temp2.tv_sec-temp1.tv_sec)*1000000L)/10;
	fprintf(log,"%ld,",elapsed_u_time);
	fprintf(log,"%f,",((float)bits)/(float)elapsed_u_time );
	
	//printf("READ\n");
	
	unsigned char *readVal = (unsigned char*) malloc(sizeof(unsigned char)*bits);
	
	for (j=0;j<bits;j++) { //read
		readVal[j] = 0;		
	}
	gettimeofday(&temp1,NULL);
	for(k=0;k<10; k++){
		wishbone_read(readVal,bits,(int)0x1000);
	}
	gettimeofday(&temp2,NULL);
	
	elapsed_u_time = ((temp2.tv_usec-temp1.tv_usec)+(temp2.tv_sec-temp1.tv_sec)*1000000L)/10;
	fprintf(log,"%ld,",elapsed_u_time);
	fprintf(log,"%f,",((float)bits)/(float)elapsed_u_time );
	fprintf(log,"\n");
	
	fclose(log);
	close(fd);
	free(writeVal);
	free(readVal);
	return 0 ;
}

