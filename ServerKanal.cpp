#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define MAXLINE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

int main(int argc, char **argv) {
	int readfd = -1;
	int writefd = -1;
	pid_t childpid = 0;
	size_t n;
	char str[MAXLINE];
	char name[MAXLINE];
	unlink(FIFO1);
	unlink(FIFO2);
	
	if (mkfifo(FIFO1, FILE_MODE) == EEXIST) std::cout<<"\n Pipes is exists"<<std::endl;
	if (mkfifo(FIFO2, FILE_MODE) == EEXIST) std::cout<<"\n Pipes is exists"<<std::endl;
	
	while(1){
		readfd = open(FIFO1, O_RDONLY);
		while ((n = read(readfd, name, MAXLINE)) > 0) {
			name[n]=0;
			break;
		}
		writefd = open(FIFO2, O_WRONLY);
		if ((writefd != -1)) {
			strcpy(str,"Hello, ");
			write(writefd, str, strlen(str));
			close(readfd);
			close(writefd);
			//close(fin);
			unlink(FIFO1);
			unlink(FIFO2);
		} 
		else std::cout<<"Can't open pipes..."<<std::endl;
		return 1;
	}
}

