## SERVER ##
SERVER_OBJS = main_server.o server.o
SERVER_APP_DIR = ./bin
SERVER_APP_NAME = server_app

## CLIENT ##
CLIENT_OBJS = main_client.o client.o game.o
CLIENT_APP_DIR = bin
CLIENT_APP_NAME = client_app

CC = g++
# Uncomment for Linux compile
# CFLAGS = -c -std=c++14 -I./include/SFML-2.4.2-linux/include
# LFLAGS = -L./include/SFML-2.4.2-linux/lib -lsfml-network -lsfml-system

# Uncomment for osx compile
CFLAGS = -c -std=c++14 -I/usr/local/Cellar/sfml/2.4.2/include
LFLAGS = -L/usr/local/Cellar/sfml/2.4.2/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

## `make all` or `make` will make this target
all: $(SERVER_OBJS) $(CLIENT_OBJS)
	make server_app
	make client_app

## SERVER ##
server_app: $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERVER_APP_DIR)/$(SERVER_APP_NAME) $(LFLAGS)

main_server.o: main_server.cpp server.h
	$(CC) $(CFLAGS) main_server.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp

## CLIENT ##
client_app: $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT_APP_DIR)/$(CLIENT_APP_NAME) $(LFLAGS)

main_client.o: main_client.cpp game.h
	$(CC) $(CFLAGS) main_client.cpp

game.o: game.cpp client.h
	$(CC) $(CFLAGS) game.cpp

client.o: client.cpp
	$(CC) $(CFLAGS) client.cpp

## UTILITY ##
clean:
	rm $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_APP_DIR)/$(SERVER_APP_NAME) $(CLIENT_APP_DIR)/$(CLIENT_APP_NAME)
