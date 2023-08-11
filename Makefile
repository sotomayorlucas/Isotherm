CC = g++
CFLAGS = -Wall -g 

.PHONY: all clean

all: main

main: main.o horno.o solsistema.o
	$(CC) $(CFLAGS) $^ -o $@ 

horno.o: horno.cpp horno.h
	$(CC) $(CFLAGS) -c $< -o $@

solsistema.o: solsistema.cpp solsistema.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp horno.h solsistema.h
	$(CC) $(CFLAGS) -c $< -o $@ 


.PHONY: clean

clean:
	rm -f *.o
	rm -f main



