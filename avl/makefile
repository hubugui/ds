AR=ar
CC=gcc
DEL=rm -rf
MK=mkdir
OUT=objs
RM=rmdir /s /q
CFLAGS=-Wall -O3 -lm -I../trie
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
TARGET=$(notdir $(CURDIR))
LIBS=lib$(TARGET).a
ANOTHER_LIBS=libtrie.a

all: $(TARGET)

$(TARGET): $(LIBS)
	$(CC) -o $@ $^ $(CFLAGS) 
	#$(DEL) $(LIBS)

$(LIBS): $(OBJS)
	$(AR) -x $(ANOTHER_LIBS)
	$(AR) -crsv $@ *.o
	$(DEL) *.o

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(DEL) $(LIBS)*
	-$(DEL) *.o
	-$(DEL) *.out
	-$(DEL) *.lib
	-$(DEL) $(TARGET) 

rebuild: clean all
