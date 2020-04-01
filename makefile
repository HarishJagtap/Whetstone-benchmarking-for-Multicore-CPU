IDIR = src/include
ODIR = bin
CDIR = src
RDIR = result

DEPS = $(wildcard $(IDIR)/*.h)
CFILE = $(wildcard $(CDIR)/*.c)
_OBJ = $(CFILE:.c=.obj)
OBJ = $(_OBJ:$(CDIR)/%=$(ODIR)/%)

ifeq ($(OS),Windows_NT)
CC = cl
CFLAG = /c
OFLAG = /Fo
IFLAG = /I $(IDIR)
ONAME = /Fe
DEBUG = /Zi
OPTIMISEOFF = /Od
DLIB =
MISC = /nologo
$(info Windows OS detected)
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CC = gcc
CFLAG = -c
OFLAG = -o
IFLAG = -I $(IDIR)
ONAME = -o
DEBUG = -g
OPTIMISEOFF = -O0
DLIB = -lm -lpthread
MISC =
$(info Linux OS detected)
else
$(error Program does not support this operating system)
endif
endif

$(ODIR)/benchmark : directories $(OBJ)
	$(CC) $(OPTIMISEOFF) $(ONAME)$@ $(OBJ) $(IFLAG) $(DLIB) $(MISC)

directories :
	mkdir -p $(ODIR) $(RDIR)

$(ODIR)/%.obj : $(CDIR)/%.c $(DEPS)
	$(CC) $(OPTIMISEOFF) $(CFLAG) $< $(OFLAG)$@ $(IFLAG) $(MISC)

.PHONY: clean directories

clean:
	rm -f $(ODIR)/*.obj
	rm -f $(ODIR)/*.exe