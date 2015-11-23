#for use on Windows:

#MKDIR=mkdir
#RM=del /y

CXXFLAGS+=-static-libgcc -static-libstdc++
CFLAGS+=-static-libgcc

export

OUTDIR=out

all: $(OUTDIR)
	$(MAKE) -C Hearts

debug: export CXXFLAGS+=-g
debug: clean all

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
ifeq ($(OS),Windows_NT)
	del /S /Q *.o *.a *.exe $(OUTDIR)\*
	rmdir /S /Q $(OUTDIR)
else ifeq ($(shell uname), Linux)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	rm $(OUTDIR)/* -f
	find . -empty -type d -delete
endif

rebuild: clean all
