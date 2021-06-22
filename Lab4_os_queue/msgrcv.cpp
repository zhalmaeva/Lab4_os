#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSG_R (S_IRUSR | S_IRGRP | S_IROTH)
#define MAXMSG (8192 + sizeof(long))
int main(int argc, char **argv)
{
	int c, flag, mqid;
	long type;
	ssize_t n;
	struct msgbuf *buff;
	type = flag = 0;
	while ( (c = getopt(argc, argv, "nt:")) != -1) {
		switch (c) {
			case 'n':
			flag |= IPC_NOWAIT;
			break;
			case 't':
			type = atol(optarg);
			break;
		}
	}
	if (optind != argc - 1)
	{
		printf("usage: msgrcv [ -n ][ -t type ]<path_to_file>");
		return 0;
	}
	mqid = msgget(ftok(argv[optind], 0), MSG_R);
	buff = (msgbuf*) malloc(MAXMSG);
	n = msgrcv(mqid, buff, MAXMSG, type, flag);
	printf("read %d bytes, type = %ld\n", n, buff->mtype);
	return 0;
}
