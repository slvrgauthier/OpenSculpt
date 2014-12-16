CC = g++
CXXFLAGS = -w
TMPFOLDER=tmp
BUILDFOLDER=_build


all: OpenSculpt

OpenSculpt: main.o
        @ if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
        @ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
        @ $(CC) $(CXXFLAGS) $(TMPFOLDER)/main.o -o $(BUILDFOLDER)/OpenSculpt

main.o: main.cpp
        @ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
        $(CC) $(CXXFLAGS) -o $(TMPFOLDER)/main.o -c $<

clean:
        rm -rf $(TMPFOLDER)/*.o
        rm -rf $(BUILDFOLDER)/*
