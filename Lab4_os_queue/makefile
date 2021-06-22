All: msgcreate msgsnd msgrcv msgctl
msgcreate: msgcreate.o
	g++ $^ -o $@
msgsnd: msgsnd.o
	g++ $^ -o $@
msgrcv: msgrcv.o
	g++ $^ -o $@
msgctl: msgctl.o
	g++ $^ -o $@
msgcreate.o: msgcreate.cpp
	g++ -c -MD $<
msgsnd.o: msgsnd.cpp
	g++ -c -MD $<
msgrcv.o: msgrcv.cpp
	g++ -c -MD $<
msgctl.o: msgctl.cpp
	g++ -c -MD $<
