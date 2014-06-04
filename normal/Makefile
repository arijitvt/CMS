target=cms

cc=g++
cflags= -c -I.  -I$(boost_lib)
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
