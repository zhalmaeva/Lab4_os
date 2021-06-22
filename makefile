All: Client Server
Client: ClientKanal.o
	g++ $^ -o $@
ClientKanal.o: ClientKanal.cpp
	g++ -c -MD $<
Server: ServerKanal.o
	g++ $^ -o $@
ServerKanal.o: ServerKanal.cpp
	g++ -c -MD $<
