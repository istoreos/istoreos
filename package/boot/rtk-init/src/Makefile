CC ?= gcc
CFLAGS ?= -Wall
MAIN_OBJ = main.o
OBJS = cmdline.o

all: init

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

init: $(OBJS) $(MAIN_OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(MAIN_OBJ)

clean:
	rm -f init *.o
