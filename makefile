#for use on Windows:

#MKDIR=mkdir
#RM=del /y

OUTDIR=out

all: $(OUTDIR)
	$(MAKE) -C Hearts

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
