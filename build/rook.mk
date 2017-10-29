DEBUGFILES := $(shell find $(SRCDIR)/dev/debugnew -type f -name *.$(SRCEXT))
BOARDFILES := $(shell find $(SRCDIR)/dev/board -type f -name *.$(SRCEXT))
LOADER := $(shell find $(SRCDIR)/ext/loader -type f -name *.$(SRCEXT))
RUNTIME := $(shell find $(SRCDIR)/runtime -type f -name *.$(SRCEXT))
ROOKFILES := $(shell find $(SRCDIR)/rook -type f -name *.$(SRCEXT))

rook_parser: $(SRCDIR)/rook/grammar/parser.yy
	bison -d -v $(SRCDIR)/rook/grammar/parser.yy -o $(SRCDIR)/rook/parser.tab.cpp

rook_lexer: $(SRCDIR)/rook/grammar/lexer.l
	flex --outfile=$(SRCDIR)/rook/lexer.yy.cpp  $<

rook: rook_parser rook_lexer
	$(CC) $(CXXSTD) $(INC) $(BOARDFILES) $(DEBUGFILES) $(RUNTIME) $(LOADER) $(ROOKFILES) -o $(TARGETDIR)/rook