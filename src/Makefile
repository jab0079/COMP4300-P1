# Source-level Makefile

include ../include.txt

SOURCE_ACCUM_DIR=accumCode/
SOURCE_STACK_DIR=stackCode/
SOURCE_UTILS_DIR=util/

SOURCES_ACCUM=$(wildcard $(SOURCE_ACCUM_DIR)*.cc)
SOURCES_STACK=$(wildcard $(SOURCE_STACK_DIR)*.cc)
SOURCES_UTILS=$(wildcard $(SOURCE_UTILS_DIR)*.cc)

OBJECTS_ACCUM=$(patsubst $(SOURCE_ACCUM_DIR)%.cc,%.o,$(SOURCES_ACCUM))
OBJECTS_STACK=$(patsubst $(SOURCE_STACK_DIR)%.cc,%.o,$(SOURCES_STACK))
OBJECTS_UTILS=$(patsubst $(SOURCE_UTILS_DIR)%.cc,%.o,$(SOURCES_UTILS))

all: utils stackSim accumSim

stackSim: $(OBJECTS_STACK) utils
	@mv *.o ../$(OBJECT_DIR)
	$(CC) -o $(EXE_STACK) ../$(OBJECT_DIR)/$(OBJECTS_STACK) ../$(OBJECT_DIR)/$(OBJECTS_UTILS)
	@mv $(EXE_STACK) ../$(BIN_DIR)
	
$(OBJECTS_STACK):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_STACK)

accumSim: $(OBJECTS_ACCUM) utils
	@mv *.o ../$(OBJECT_DIR)
	$(CC) -o $(EXE_ACCUM) ../$(OBJECT_DIR)/$(OBJECTS_ACCUM) ../$(OBJECT_DIR)/$(OBJECTS_UTILS)
	@mv $(EXE_ACCUM) ../$(BIN_DIR)

$(OBJECTS_ACCUM):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_ACCUM)
	
utils: $(OBJECTS_UTILS)
	@mv *.o ../$(OBJECT_DIR)

$(OBJECTS_UTILS):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_UTILS)
	
	
clean:
	