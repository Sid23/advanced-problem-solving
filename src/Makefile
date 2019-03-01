IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = recursiveFunctions.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o recursiveFunctions.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f main $(ODIR)/*.o *~ core $(INCDIR)/*~ 