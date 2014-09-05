# Top-level Makefile

# This file includes all of our project-specific elements
include include.txt


# When 'make' is run without qualifiers, this rule is the main
# rule it goes to first. The '@' means not to echo the statements
# back to standard output. The 'obj' and 'bin' means that 'all'
# is dependant on these two rules. They are run before the rest
# of the code is run.
all: obj bin
	@cd $(SOURCE_DIR); make
	@echo "Done...";

# This rule tests to see if OBJECT_DIR is already a directory
# within this current directory. If it isnt, then it creates
# the directory.
obj:
	@test -d $(OBJECT_DIR) || mkdir $(OBJECT_DIR)
	
bin:
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	
clean:
	@cd $(SOURCE_DIR); make clean
	rm -rf $(BIN_DIR) $(OBJECT_DIR);
	@echo "Done..."