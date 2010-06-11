all: libZkDns-cpp.a

OBJECTS = \
	RecordProvider.o \
	ZkDns.o \

.PHONY: clean

%.o: %.h %.cpp
	g++ -g -c $*.cpp -o $@

libZkDns-cpp.a: $(OBJECTS)
	ar rcs $@ $^
	ranlib $@

clean:
	rm -f *.o *.a
