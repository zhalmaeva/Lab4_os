All: server client
server: server.o
	g++ $^ -o $@
server.o: server.cpp
	g++ -c -MD $<
client: client.o
	g++ $^ -o $@
client.o: client.cpp
	g++ -c -MD $<
