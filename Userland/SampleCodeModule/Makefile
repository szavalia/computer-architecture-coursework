include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
#SOURCES_ASM=$(wildcard asm/*.asm)
#OBJECTS=$(SOURCES:.c=.o)
#OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE) #$(OBJECTS_ASM) $(OBJECTS)
#	$(GCC) $(GCCFLAGS) $(OBJECTS) $(OBJECTS_ASM) _loader.o -o ../$(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) -o ../$(MODULE)

#%.o: %.c
#	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

#%.o : %.asm
#	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm/*.o *.o

.PHONY: all clean print
