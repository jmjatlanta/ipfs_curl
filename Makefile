CC=gcc
CFLAGS=-Iinclude -std=gnu++11 -I../../curlcpp/include -I../../rapidjson/include
DEPS = ipfs.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
libipfs_curl.a: $(DEPS)
	ar rcs $@ $^
	
clean:
	rm -f *.o;
	rm -f libipfs_curl.a
	
all: libipfs_curl.a