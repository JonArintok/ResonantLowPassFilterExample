
primaryTarget = ResLPFilterExample

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lSDL2 -lm -Wall

$(primaryTarget): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(primaryTarget)
