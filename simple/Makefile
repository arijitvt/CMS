target=cms

cc=g++

cflags= -std=c++0x -c -g -I.  -I$(boost_inc)  -DDEBUG
lflags= -L$(boost_lib) -lboost_system -lboost_thread -pthread
                                         

objs= Lexer.o Parser.o Commands.o MarketPlace.o main.o

rm=rm -rf

all:$(objs)
	$(cc) $(objs) -o $(target) $(lflags)


%.o:%.cpp 
	$(cc) $(cflags) -o $@ $<

ServerObj=Server.o  server_driver.o

server:$(ServerObj)
	$(cc) $(ServerObj) -o Server $(lflags)


ClientObj=client.o

client:$(ClientObj)
	$(cc) $(ClientObj) -o Client $(lflags)

clean:
	$(rm) *.o
	$(rm) $(target)
	$(rm) Server
	$(rm) Client
