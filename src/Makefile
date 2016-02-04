OBJS = buffer.o crustache.o houdini_html.o stack.o main.o
PROG = main
TARGET_C = gcc
TARGET_C_OPTS = -Wall -O2

all: $(PROG)

$(OBJS): %.o: %.c
		$(TARGET_C) $(TARGET_C_OPTS) -c $< -o $@

$(PROG): $(OBJS)
		$(TARGET_C) $(TARGET_C_OPTS) $^ -o $@

clean:
	rm -f *.o

