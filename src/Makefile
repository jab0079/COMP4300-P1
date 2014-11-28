# Source-level Makefile

include ../include.txt

SOURCE_ACCUM_DIR=accumCode/
SOURCE_STACK_DIR=stackCode/
SOURCE_GPR_DIR=gprCode/
SOURCE_PIPE_DIR=pipeCode/
SOURCE_SCO_DIR=scoCode/
SOURCE_UTILS_DIR=util/

SOURCES_ACCUM=$(wildcard $(SOURCE_ACCUM_DIR)*.cc)
SOURCES_STACK=$(wildcard $(SOURCE_STACK_DIR)*.cc)
SOURCES_GPR=$(wildcard $(SOURCE_GPR_DIR)*.cc)
SOURCES_PIPE=$(wildcard $(SOURCE_PIPE_DIR)*.cc)
SOURCES_SCO=$(wildcard $(SOURCE_SCO_DIR)*.cc)
SOURCES_UTILS=$(wildcard $(SOURCE_UTILS_DIR)*.cc)



OBJECTS_ACCUM=$(patsubst $(SOURCE_ACCUM_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_ACCUM))
OBJECTS_STACK=$(patsubst $(SOURCE_STACK_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_STACK))
OBJECTS_GPR=$(patsubst $(SOURCE_GPR_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_GPR))
OBJECTS_PIPE=$(patsubst $(SOURCE_PIPE_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_PIPE))
OBJECTS_SCO=$(patsubst $(SOURCE_SCO_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_SCO))
OBJECTS_UTILS=$(patsubst $(SOURCE_UTILS_DIR)%.cc,../$(OBJECT_DIR)%.o,$(SOURCES_UTILS))

all: utils stackSim accumSim gprSim pipeSim scoSim

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
	
gprSim: utils $(OBJECTS_GPR) 
	$(CC) -o $(EXE_GPR) $(OBJECTS_GPR) $(OBJECTS_UTILS)
	@mv $(EXE_GPR) ../$(BIN_DIR)

$(OBJECTS_GPR):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_GPR)
	@mv *.o ../$(OBJECT_DIR)
	
pipeSim: utils $(OBJECTS_PIPE) 
	$(CC) -o $(EXE_PIPE) $(OBJECTS_PIPE) $(OBJECTS_UTILS)
	@mv $(EXE_PIPE) ../$(BIN_DIR)

$(OBJECTS_PIPE):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_PIPE)
	@mv *.o ../$(OBJECT_DIR)
	
scoSim: utils $(OBJECTS_SCO) 
	$(CC) -o $(EXE_SCO) $(OBJECTS_SCO) $(OBJECTS_UTILS)
	@mv $(EXE_SCO) ../$(BIN_DIR)

$(OBJECTS_SCO):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_SCO)
	@mv *.o ../$(OBJECT_DIR)
	
utils: $(OBJECTS_UTILS)

$(OBJECTS_UTILS):
	$(CC) $(CFLAGS) -I../$(INCLUDE_DIR) -c $(SOURCES_UTILS)
	@mv *.o ../$(OBJECT_DIR)
	
	
clean:
	