CXX = mpic++
WARN = -Wall
CFLAGS = $(WARN) -I/data/homezvol1/hartlemt/ecf/include 
LDFLAGS = $(WARN) -lecf -L/data/homezvol1/hartlemt/ecf/lib

OBJS = SymbRegEvalOp.o \
       main.o

BINFILE = symbreg

.PHONY = all clean

all: $(BINFILE)

$(BINFILE): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(BINFILE)

%.o: %.cpp SymbRegEvalOp.h
	$(CXX) $(CFLAGS) $< -c -o $@

clean:
	rm -f *~ $(OBJS) $(BINFILE)
