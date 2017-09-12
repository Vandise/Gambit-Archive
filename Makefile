#Compiler and Linker
CC          := clang++

#The Target Binary Program
TARGET      := matec
TESTTARGET  := test_suite

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
TESTDIR     := test
INCDIR      := inc
LIBDIR      := lib
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

current_dir = $(shell pwd)

#Flags, Libraries and Includes
CXXSTD      := -std=c++11 -Wno-deprecated-register
CFLAGS      := $(CXXSTD) -fopenmp -Wall -O3 -g
#LIB        := -fopenmp -lm -larmadillo
DYNLIBPARAM := -dynamiclib
INC         := -I$(INCDIR) -Isrc -Isrc/test -I$(LIBDIR) -I/usr/local/opt/flex/include
PARSER_LEXER =  parser lexer

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------

SOURCES     := $(shell find $(SRCDIR) $(LIBDIR) -type f -name *.$(SRCEXT) -not -path "$(SRCDIR)/gambit/*")
#SOURCES     := $(shell find $(SRCDIR) $(LIBDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
MAINOBJS    := $(shell echo $(OBJECTS) | sed 's/[^ ]*test[^ ]* *//g')
TESTOBJS    := $(filter-out $(MAINOBJS), $(OBJECTS))

#Defauilt Make
all: directories $(TARGET) $(TESTTARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
	@cp $(RESDIR)/* $(TARGETDIR)/

#Make the Directories
directories:
	mkdir -p $(TARGETDIR)
	mkdir -p $(BUILDDIR)
	mkdir -p $(TESTDIR)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(RESDIR)


#Clean only Objecst
clean:
	$(RM) -rf $(BUILDDIR)
	$(RM) -rf $(TARGETDIR)
	$(RM) -r $(LIBDIR)/*.so
	$(RM) -f $(TARGETDIR)
	$(RM) -f src/gambit/parser.*
	$(RM) -f src/gambit/location.hh
	$(RM) -f src/gambit/position.hh
	$(RM) -f src/gambit/stack.hh
	$(RM) -f src/gambit/lexer.yy.cpp

#Clean only Objecst
watch: $(SRCDIR)
	@fswatch -o $^/*.cpp | xargs -I{} make 


#Full Clean, Objects and Binaries
cleaner: clean
	$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
-include build/gambit.mk

#Link
$(TARGET): $(filter-out $(TESTOBJS),$(OBJECTS))
	$(CC) -o $(TARGETDIR)/$(TARGET) $^

$(TESTTARGET): $(filter-out $(BUILDDIR)/$(TARGET).$(OBJEXT),$(OBJECTS))
	$(CC) -o $(TARGETDIR)/$(TESTTARGET) $^

#Compile src
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	$(CC) $(CFLAGS) $(INC) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT) 
	cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean cleaner