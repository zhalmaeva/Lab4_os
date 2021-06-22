#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <error.h>
#include <unistd.h>
#include <fcntl.h>
#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
int main(int argc, char **argv)
	{
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
	return 0;
}

