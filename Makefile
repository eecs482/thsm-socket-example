CC = g++ -Wall -Wextra -pedantic -std=c++17 -g

all: server client

server: server.cpp
	$(CC) $^ -o $@

client: client.cpp
	$(CC) $^ -o $@

clean:
	rm -f server client