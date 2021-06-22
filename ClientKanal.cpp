#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include<string>
#include <fstream>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define MAXLINE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

int main(int argc, char **argv) {
	int readfd = -1, writefd = -1;
	pid_t childpid = 0;
	size_t n = 0;
	char str[MAXLINE];
	char name[MAXLINE];
	while (1){
		std::cout<<"Please, enter your name: "<<std::endl;
		std::string st;
		std::cin>>st;
		for(int i=0; i<st.size(); i++)
			name[i] = st[i];

		writefd = open(FIFO1, O_WRONLY, 0);
		write(writefd, name, strlen(name));
				
		readfd = open(FIFO2, O_RDONLY, 0);
		if (readfd != -1) {
			while ((n = read(readfd, str, MAXLINE)) > 0) {
				str[n]=0;
				std::cout<<str<<name<<std::endl;
				break;
	 		}
			close(readfd);
			close(writefd);
		 	break;
		}
	}
	return 1;
}
