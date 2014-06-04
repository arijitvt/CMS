target=cms

cc=g++
cflags= -I. -c
lflags=
objs= Parser.o main.o

rm=rm -rf

all:$(objs)
	$(cc) $(objs) -o $(target) $(lflags)


%.o:%.cpp 
	$(cc) $(cflags) -o $@ $<

clean:
	$(rm) *.o
	$(rm) $(target)
