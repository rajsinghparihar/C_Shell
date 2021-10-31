CFLAGS = -g -Wall

turtle: turtle.o run_command.o cd.o redirection.o pipe.o
	gcc -o turtle $(CFLAGS) turtle.o run_command.o cd.o redirection.o pipe.o

clean:
	rm -f *.o turtle

turtle.o: turtle.c
	gcc $(CFLAGS) -c turtle.c

run_command.o: run_command.c runcommand.h
	gcc $(CFLAGS) -c run_command.c

cd.o: cd.c runcommand.h
	gcc $(CFLAGS) -c cd.c

redirection.o: redirection.c runcommand.h
	gcc $(CFLAGS) -c redirection.c

pipe.o: pipe.c runcommand.h
	gcc $(CFLAGS) -c pipe.c
