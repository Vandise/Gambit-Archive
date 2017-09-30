SQLITE_FILES := $(shell find $(EXTDIR)/sqlite -type f -name *.c)
SQLITE_EXT_FILES := $(shell find $(EXTDIR)/sqlite -type f -name *.$(SRCEXT))
RUNTIME_FILES := $(shell find $(SRCDIR)/runtime/shared -type f -name *.$(SRCEXT))
DEBUGFILES := $(shell find $(SRCDIR)/dev/debugnew -type f -name *.$(SRCEXT))

sqlite_src: $(SQLITE_FILES)
	mkdir -p $(EXTDIR)/sqlite/obj
	$(GCC) -c $(SQLITE_FILES) -o $(EXTDIR)/sqlite/obj/sqlite.o

ext_sqlite:
	$(CC) $(CXXSTD) $(INC) $(DYNLIBPARAM) $(SQLITE_EXT_FILES) $(RUNTIME_FILES) $(EXTDIR)/sqlite/obj/sqlite.o $(DEBUGFILES) -o $(LIBDIR)/sqlite.so
