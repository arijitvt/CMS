cc=gcc
target=output


cflags= -c -g
lflags= -lfl

objs= parser.o  lex.o interpreter.o

all:$(objs)
	$(cc) $(objs) -o $(target) $(lflags)


interpreter.o: interpreter.c srcty.h
	$(cc) $(cflags) -o $@ $<

lex.o:lex.c
	$(cc) $(cflags) -o lex.o lex.c

parser.o:parser.c
	$(cc) $(cflags) -o parser.o parser.c

parser.c:parser.y
	yacc  -d parser.y -o parser.c


lex.c:lex.l
	flex  -olex.c lex.l


clean:
	rm -rf $(target)
	rm -rf *.o
	rm -rf lex.c
	rm -rf parser.c
	rm -rf parser.h
