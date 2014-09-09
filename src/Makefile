# Source-level Makefile

include ../include.txt

SOURCE_ACCUM_DIR=accumCode/
SOURCE_STACK_DIR=stackCode/
SOURCE_UTILS_DIR=util/

SOURCES_ACCUM=$(wildcard $(SOURCE_ACCUM_DIR)*.cc)
SOURCES_STACK=$(wildcard $(SOURCE_STACK_DIR)*.cc)
SOURCES_UTILS=$(wildcard $(SOURCE_UTILS_DIR)*.cc)

OBJECTS_ACCUM=$(patsubst $(SOURCE_ACCUM_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_ACCUM))
OBJECTS_STACK=$(patsubst $(SOURCE_STACK_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_STACK))
OBJECTS_UTILS=$(patsubst $(SOURCE_UTILS_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_UTILS))

all: utils stackSim accumSim

stackSim: utils $(OBJECTS_STACK)
	$(CC) -o $(EXE_STACK) $(OBJECTS_STACK) $(OBJECTS_UTILS)
	@mv $(EXE_STACK) ../$(BIN_DIR)
	
$(OBJECTS_STACK):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_STACK)
	@mv *.o ../$(OBJECT_DIR)

accumSim: utils $(OBJECTS_ACCUM) 
	$(CC) -o $(EXE_ACCUM) $(OBJECTS_ACCUM) $(OBJECTS_UTILS)
	@mv $(EXE_ACCUM) ../$(BIN_DIR)

$(OBJECTS_ACCUM):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_ACCUM)
	@mv *.o ../$(OBJECT_DIR)
	
utils: $(OBJECTS_UTILS)

$(OBJECTS_UTILS):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_UTILS)
	@mv *.o ../$(OBJECT_DIR)
	
	
clean:
	