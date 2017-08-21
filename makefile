OBJS = main.o server.o client.o
APP_DIR = .
APP = application
CC = g++
CFLAGS = -c -pthread -std=c++14 -I/usr/local/Cellar/sfml/2.4.2/include
LFLAGS = -L/usr/local/Cellar/sfml/2.4.2/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

application: $(OBJS)
	$(CC) $(OBJS) -o $(APP_DIR)/$(APP) $(LFLAGS)

main.o: main.cpp server.h client.h
	$(CC) $(CFLAGS) main.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp

client.o: client.cpp
	$(CC) $(CFLAGS) client.cpp

clean:
	rm $(OBJS) $(APP_DIR)/$(APP)
