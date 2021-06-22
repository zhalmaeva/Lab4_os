#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#define MSG_W (S_IWUSR)
int main(int argc, char **argv)
{
	int mqid;
	size_t len;
	long type;
	struct msgbuf *ptr;
	if (argc != 4)
	{
		printf("usage: msgsnd <path_to_file><#bytes><type>");
		return 0;
	}
	len = atoi(argv[2]);
	type = atoi(argv[3]);
	mqid = msgget(ftok(argv[1], 0), MSG_W);
	ptr = (msgbuf*) calloc(sizeof(long) + len, sizeof(char));
	ptr->mtype = type;
	msgsnd(mqid, ptr, len, 0);
	return 0;
}
