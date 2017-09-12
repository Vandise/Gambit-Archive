GAMBITFILES := $(shell find $(SRCDIR)/gambit -type f -name *.$(SRCEXT))
DEBUGFILES := $(shell find $(SRCDIR)/dev/debugnew -type f -name *.$(SRCEXT))
#INSTRFILES := $(shell find $(SRCDIR)/generator -type f -name *.$(SRCEXT))
INSTRFILES :=

parser: $(SRCDIR)/gambit/grammar/parser.yy
	bison -d -v $(SRCDIR)/gambit/grammar/parser.yy -o $(SRCDIR)/gambit/parser.tab.cpp
	#$(CC) $(CFLAGS) $(INC) -c -o $(BUILDDIR)/parser.o $(SRCDIR)/gambit/parser.tab.cpp

lexer: $(SRCDIR)/gambit/grammar/lexer.l
	flex --outfile=$(SRCDIR)/gambit/lexer.yy.cpp  $<
	#$(CC)  $(CFLAGS) $(INC) -c src/gambit/lexer.yy.cpp -o $(BUILDDIR)/lexer.o

gambit: parser lexer
	$(CC) $(CXXSTD) $(INC) $(DYNLIBPARAM) $(GAMBITFILES) $(DEBUGFILES) $(INSTRFILES) -o $(LIBDIR)/gambit.so