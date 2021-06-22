#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include<string>
#include<iostream>
#define MSG_R (S_IRUSR | S_IRGRP | S_IROTH)
#define MAXMSG (4056 - sizeof(long))
#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MSG_W (S_IWUSR)
int main(int argc, char **argv)
{
	int c, oflag, mqid;
	long type = 10;
	oflag = SVMSG_MODE | IPC_CREAT;
	while ( (c = getopt(argc, argv, "e")) != -1) {
		switch (c) {
			case 'e':
			oflag |= IPC_EXCL;
			break;
		}
	}
	if (optind != argc - 1)
	{
		printf("usage: msgcreate [ -e ] <path_to_file>");
		return 0;
	}
	mqid = msgget(ftok(argv[optind], 0), oflag);
	
	struct Out {
		long mtype;
		int first;
		int second;
	} msgOut;
	struct In {
		long mtype;
		int sum;
	} msgIn;
	msgOut.mtype=1;
	std::cin>>msgOut.first>>msgOut.second; 
	int len = sizeof(struct Out) - sizeof(long);
	c = msgsnd( mqid, &msgOut, len, 0);
	
	while(1){
		if ((c = msgrcv(mqid, &msgIn, MAXMSG, 2, 0)) >0){
			std::cout<<"sum = "<<msgIn.sum<<std::endl;
			break;
		}
	}
	return 0;
}
