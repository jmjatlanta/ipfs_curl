CC=gcc
CFLAGS=-I../include -std=gnu++11 -I../../../curlcpp/include -I../../../rapidjson/include
DEPS = ipfs.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
../build/libipfs_curl.a: $(DEPS)
	ar rcs $@ $^
	
clean:
	rm -f *.o;
	rm -f ../build/libipfs_curl.a
	
all: ../build/libipfs_curl.a