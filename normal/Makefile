target=cms

cc=g++
cflags= -std=c++0x -c -g -I.  -I$(boost_lib)  -DDEBUG
lflags=
objs= Lexer.o Parser.o main.o

rm=rm -rf

all:$(objs)
	$(cc) $(objs) -o $(target) $(lflags)


%.o:%.cpp 
	$(cc) $(cflags) -o $@ $<

clean:
	$(rm) *.o
	$(rm) $(target)
