CC=g++
CFLAGS=-I../include -I../../../curlcpp/include -I../../../rapidjson/include -std=gnu++11
LFLAGS=-L../../../curlcpp/build -L../build -L/usr/lib
DEPS = TestIt.o

%o: %cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
../build/TestIt: $(DEPS)
	$(CC) $(LFLAGS) -o $@ $^ -lipfs_curl -lcurlcpp -lcurl -stdlib=libc++
	
clean:
	rm -f *.o;
	rm -f ../build/TestIt
	
all: TestIt