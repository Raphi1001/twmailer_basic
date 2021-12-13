all: client server

client: ./src/client/clientMain.cpp
	g++ -std=c++14 -Wall -Werror -o ./bin/client ./src/client/clientMain.cpp ./src/client/client.cpp ./src/client/client.h

server: ./src/server/serverMain.cpp
	g++ -std=c++14 -Wall -Werror -o ./bin/server ./src/server/serverMain.cpp ./src/server/server.cpp ./src/server/server.h -pthread

clean:
	rm bin/client
	rm bin/server
