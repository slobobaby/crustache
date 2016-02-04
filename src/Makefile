OBJS = buffer.o crustache.o houdini_html.o stack.o
TARGET_C = gcc
TARGET_C_OPTS = -Wall -O2

all: $(OBJS)

$(OBJS): %.o: %.c
		$(TARGET_C) $(TARGET_C_OPTS) -c $< -o $@

clean:
	rm -f *.o

