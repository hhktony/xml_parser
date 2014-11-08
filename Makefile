CC = gcc
CFLGAS = `xml2-config --cflags` -Wall -W -g #-pg
LDFLAGS = `xml2-config --libs` #-lpthread #-pg
objs = $(patsubst %.c, %.o, $(wildcard *.c))

test : $(objs)
	$(CC) $^ $(LDFLAGS) -o $@

%.o : %.c
	$(CC) $(CFLGAS) -c $<

tags:
	ctags -R *.c *.h

clean:
	$(RM) test $(objs) a.out *~ tags

.PHONY: clean test tags
