## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -g -std=c++11 -Wno-deprecated

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
	main.cpp \
	Matrix/Contstructors.cpp \
	Matrix/Operators.cpp \
	Matrix/Private.cpp \
	Matrix/RowOperations.cpp \
	Matrix/Trivial.cpp \
	Matrix/Friend.cpp \
	$(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): main.o Matrix/Constructors.o Matrix/Operators.o Matrix/Private.o Matrix/RowOperations.o Matrix/Trivial.o Matrix/Friend.o
	$(CC) -o execute main.o Matrix/Constructors.o Matrix/Operators.o Matrix/Private.o Matrix/RowOperations.o Matrix/Trivial.o Matrix/Friend.o

depend :
	makedepend ${PROGFILES}

clean:
	rm -f *.o Matrix/*.o execute

# DO NOT DELETE
