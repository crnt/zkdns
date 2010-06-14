all: zkDns

LDFLAGS=\
	-lZkDns-cpp \
	-lZkDns-c \
	-L../lib-cpp \
	-L../lib-c \
	-lldns \
	-lzookeeper_st \

.PHONY: clean

CLASS_OBJECTS=ZooKeeperRecordProvider.o ZooKeeper.o
OBJECTS=$(CLASS_OBJECTS) main.o

%.o: %.h %.cpp
	g++ -g -c $*.cpp -o $@

main.o: main.cpp
	g++ -g -c $< -o $@

zkDns: $(OBJECTS)
	g++ $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -f zkDns *.o
