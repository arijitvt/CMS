target=cms

cc=g++

cflags= -std=c++0x -c -g -I.  -I$(boost_inc)  -DDEBUG
lflags= -L$(boost_lib) -lboost_system -lboost_thread -pthread
                                         

objs= Lexer.o Parser.o Commands.o MarketPlace.o 

rm=rm -rf

#all:$(objs)
#	$(cc) $(objs) -o $(target) $(lflags)


all: server client



ServerObj=$(objs) Server.o  server_driver.o
Server.o:Server.h Server.cpp

server:$(ServerObj)
	$(cc) $(ServerObj) -o Server $(lflags)

%.o:%.cpp 
	$(cc) $(cflags) -o $@ $<

ClientObj=client.o
client.o:client.cpp

client:$(ClientObj)
	$(cc) $(ClientObj) -o Client $(lflags)

clean:
	$(rm) *.o
	$(rm) $(target)
	$(rm) Server
	$(rm) Client
