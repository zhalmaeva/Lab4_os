#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <error.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include<iostream>
#define MAXMSG (4056 - sizeof(long))
#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
int main(int argc, char **argv){
	int c, oflag, mqid;
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

	struct In {
		long mtype;
		int first;
		int second;
	} msgIn;
	struct Out {
		long mtype;
		int sum;
	} msgOut;


	while (1) {	
		if((c = msgrcv(mqid, &msgIn, MAXMSG, 1, 0))>0){
			msgOut.mtype = 2;
			msgOut.sum = msgIn.first+msgIn.second;
			int len = sizeof(struct Out) - sizeof(long);
			c = msgsnd(mqid, &msgOut, len, 0);
			break;
		}
	}	
	return 0;
}
