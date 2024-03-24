CC = g++
OBJS = binary.o memory.o state.o hw3.o
TARGET = runfile

runfile: $(OBJS)
	$(CC) $(OBJS) -o runfile

state.o : state.h state.cpp memory.o binary.o
	$(CC) memory.h -c state.cpp

memory.o : memory.h memory.cpp
	$(CC) -c memory.cpp
binary.o : binary.h binary.cpp
	$(CC) -c binary.cpp
hw3.o: hw3.cpp binary.h
	$(CC) -c hw3.cpp

.PHONY: clean
clean:
	rm -f $(OBJS)
