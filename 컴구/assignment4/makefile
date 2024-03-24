CC = g++ 
OBJS = cache.o hw4.o
TARGET = runfile

runfile: $(OBJS)
	$(CC) $(OBJS)  -o runfile

cache.o : cache.h cache.cpp
	$(CC) -c cache.cpp

hw4.o: hw4.cpp cache.o
	$(CC) -c hw4.cpp

.PHONY: clean
clean:
	rm -f $(OBJS)
