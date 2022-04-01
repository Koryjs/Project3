all: text-server.o text-client.o

text-server.c: text-server.c
	g++ text-server.c -o text-server

text-client.c: text-client.c
	g++ text-client.c -o text-client

clean:
  rm text-client
  rm text-server
