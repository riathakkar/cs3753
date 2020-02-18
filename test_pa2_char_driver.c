#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


#define BUFFER_SIZE 1024
#define DEVICE_PATH "/dev/pa2_char_driver"
int main(){
	int file=open(DEVICE_PATH,O_RDWR | O_APPEND);
	int offset=0;
	int whence;
	char option='b';
	int read_length=0;
	char temp_write[BUFFER_SIZE];
	ssize_t  data;
	if(file<0){
		printf("fail to open file\n");
	}
	else {
		printf("open file successfully\n");
	}
	while(option!='e'){  
		printf("press r to read from device\n");
		printf("press w to write to device\n");
		printf("press s to seek for values\n");
		printf("press e to quit\n");
		printf("press to contiue\n");
		printf("Enter:\n");
		scanf("%c",&option);
		if(option=='r'){
			printf("enter the number of bytes you want to read\n");
			scanf("%d",&read_length);
			char *temp=malloc(read_length);
			data=read(file,temp,read_length);
			printf("bytes read from device:%d\n",data);

		}
		else if(option=='w'){
			printf("enter data you want to write to the device:\n");
			scanf("%s",&temp_write);
			while(getchar()!='\n'); 
			printf("bytes written: %d",write(file,temp_write,strlen(temp_write)));	
		}
		else if(option=='s'){
			printf("enter offset value:\n");
			scanf("%d",&offset);
			printf("enter a value for whence:\n");
			scanf("%d",&whence);
			printf("current position: %d",lseek(file,offset,whence));
		}
		else if(option='e'){
			printf("you are quitting from the device\n");
			return 0;
		}
		getchar();
	}
	close(file);
}
