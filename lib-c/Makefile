all: libZkDns-c.a
.PHONY: clean

clib.o: clib.c
	gcc -g -c clib.c -I /usr/include/ldns/ -o clib.o

libZkDns-c.a: clib.o
	ar -cvq libZkDns-c.a clib.o
	ranlib $@

clean:
	rm -f *.o *.a
