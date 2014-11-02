AR=ar
CC=gcc
DEL=rm -rf
MK=mkdir
OUT=objs
RM=rmdir /s /q
CFLAGS=-Wall -O3 -Werror
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# GNU Scientific Lib
# LINK=-lgsl -lgslcblas

LINK=
TARGET=$(notdir $(CURDIR))
LIBS=lib$(TARGET).a

all: $(TARGET)

$(TARGET): $(LIBS) black_white test_histogram

black_white:
	$(CC) $(CFLAGS) histogram.c binary_image.c file_rw.c black_white.c -o black_white.out $(LINK)

test_histogram:
	$(CC) $(CFLAGS) histogram.c file_rw.c test_histogram.c -o test_histogram.out $(LINK)

$(LIBS): $(OBJS)
	$(AR) -r $@ $^
	-$(DEL) *.o

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-$(DEL) *.a
	-$(DEL) *.o
	-$(DEL) *.out
	-$(DEL) *.lib

rebuild: clean all