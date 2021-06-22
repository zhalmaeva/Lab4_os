#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <error.h>
int main(int argc, char **argv)
{
	int mqid;
	if (argc != 2)
	{
	 	printf("usage: msgrmid <path_to_file>");
	 	return 0;
	}
	mqid = msgget(ftok(argv[1], 0), 0);
	msgctl(mqid, IPC_RMID, NULL);
	return 0;
}
