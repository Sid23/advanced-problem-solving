IDIR=include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = recursiveFunctions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o recursiveFunctions.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(info $$Include dir is [${DEPS}])
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f main $(ODIR)/*.o *~ core $(INCDIR)/*~ 