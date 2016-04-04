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

//#define n 2048; //numero de bits

int main(int argc, char ** argv){
	int fd,address ;
	unsigned short i ;
	int j;
	int bits = atoi(argv[1]);
	unsigned short writeVal ;
	//logfile
	FILE *log;
	log = fopen("logfile.txt","a");
	
	//leitura de tempo
	struct timeval temp1,temp2;
	long elapsed_u_sec,elapsed_s_sec,elapsed_m_time,elapsed_u_time;


	if(bits%2 != 0 || bits > 2048){
		printf("not enough arguments \n");
		return 0 ;
	}

	printf("Com n = %d",bits);
	fprintf(log,"%d,",bits);
	//printf("\n");
	//printf("WRITE\n");
	//printf("\n");
	gettimeofday(&temp1,NULL);
	for (j=0;j<bits;j++) { // write
		address = (int) 0x1000 + (j<<1); //strtol(argv[1], NULL, 0);//write
		writeVal = (unsigned short) j+1; //strtol(argv[2], NULL, 0);
		//printf("Writing 0x%x @ 0x%x \n", writeVal, address);
		
		//if(wishbone_write(&writeVal, 2, address) < 2){
			//printf("Write error !");
		//}	
	}
	gettimeofday(&temp2,NULL);
	elapsed_s_sec=temp2.tv_sec-temp1.tv_sec;
	elapsed_u_sec=temp2.tv_usec-temp1.tv_usec;
	elapsed_u_time=(elapsed_s_sec)*100000+elapsed_u_sec;	
	fprintf(log,"%ld,",elapsed_u_time);
	fprintf(log,"%d,",(2048*1000)/elapsed_u_time );

	
	//printf("\n");
	//printf("READ\n");
	//printf("\n");
	gettimeofday(&temp1,NULL);
	for (j=0;j<bits;j++) { //read
		address = (int) 0x1000 + (j<<1); 
		unsigned short readVal ; //read
		
		wishbone_read(&readVal,2,address);
		//printf("0x%x \n",readVal);
		
	}
	gettimeofday(&temp2,NULL);
	elapsed_s_sec=temp2.tv_sec-temp1.tv_sec;
	elapsed_u_sec=temp2.tv_usec-temp1.tv_usec;
	elapsed_u_time=(elapsed_s_sec)*100000+elapsed_u_sec;
	fprintf(log,"%ld,",elapsed_u_time);
	fprintf(log,"%d,",(2048*1000)/elapsed_u_time );	
	fprintf(log,"\n");
	
	fclose(log);
	close(fd);
	free(bits);
	return 0 ;
}

