SQLITE_FILES := $(shell find $(EXTDIR)/sqlite -type f -name *.c)
SQLITE_EXT_FILES := $(shell find $(EXTDIR)/sqlite -type f -name *.$(SRCEXT))
RUNTIME_FILES := $(shell find $(SRCDIR)/runtime/shared -type f -name *.$(SRCEXT))
DEBUGFILES := $(shell find $(SRCDIR)/dev/debugnew -type f -name *.$(SRCEXT))

sqlite_src: $(SQLITE_FILES)
	mkdir -p $(EXTDIR)/sqlite/obj
	$(GCC) -c $(SQLITE_FILES) -fPIC -o $(EXTDIR)/sqlite/obj/sqlite.o

ext_sqlite:
	$(CC) $(CXXSTD) $(INC) -rdynamic $(DYNLIBPARAM) $(SQLITE_EXT_FILES) $(RUNTIME_FILES) $(EXTDIR)/sqlite/obj/sqlite.o $(DEBUGFILES) -Wl,--no-as-needed -ldl -o $(LIBDIR)/sqlite.so
