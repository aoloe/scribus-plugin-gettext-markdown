CFLAGS = -g -Wall $(OFLAGS) $(XFLAGS)
OFLAGS = -O3 -DNDEBUG
#OFLAGS = -pg

OBJS = tree.o compile.o

all : greg

greg : greg.o $(OBJS)
	$(CC) $(CFLAGS) -o $@-new greg.o $(OBJS)
	mv $@-new $@

ROOT	=
PREFIX	= /usr
BINDIR	= $(ROOT)$(PREFIX)/bin

install : $(BINDIR)/greg

$(BINDIR)/% : %
	cp -p $< $@
	strip $@

uninstall : .FORCE
	rm -f $(BINDIR)/greg

greg.o : greg.c

grammar : .FORCE
	./greg -o greg.c greg.g

clean : .FORCE
	rm -f *~ *.o *.greg.[cd]

spotless : clean .FORCE
	rm -f greg

.FORCE :
