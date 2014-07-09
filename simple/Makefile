target=cms

cc=g++

doc=doxygen

cflags= -std=c++0x -c -g -I.  -I$(boost_inc)  -DDEBUG
lflags= -L$(boost_lib) -lboost_system -lboost_thread -pthread -lboost_program_options
                                         

objs= Utility.o ErrorMsgs.o Exceptions.o Lexer.o Parser.o Commands.o Commodity.o  OrderInfo.o MarketPlace.o  

rm=rm -rf

#all:$(objs)
#	$(cc) $(objs) -o $(target) $(lflags)


all: server client



ServerObj=$(objs) Session.o Server.o  server_driver.o
Server.o:Server.h Server.cpp

server:$(ServerObj)
	$(cc) $(ServerObj) -o Server $(lflags)

%.o:%.cpp 
	$(cc) $(cflags) -o $@ $<

ClientObj= $(objs) client.o
client.o:client.cpp

client:$(ClientObj)
	$(cc) $(ClientObj) -o Client $(lflags)

docgen:
	$(doc) doc/config

clean:
	$(rm) $(ServerObj)
	$(rm) $(ClientObj)
	$(rm) $(objs)
	$(rm) $(target)
	$(rm) Server
	$(rm) Client
	$(rm) doc/html
