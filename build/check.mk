CHECKFILES := $(shell find $(SRCDIR)/check -type f -name *.$(SRCEXT))
DEBUGFILES := $(shell find $(SRCDIR)/dev/debugnew -type f -name *.$(SRCEXT))

check_handler:
	$(CC) $(CXXSTD) $(INC) $(DYNLIBPARAM) $(CHECKFILES) $(DEBUGFILES) -o $(LIBDIR)/check.so
