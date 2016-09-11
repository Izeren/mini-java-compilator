SRC_DIR=src
BUILD_DIR=build
VISITORS_DIR=$(SRC_DIR)/visitors
NODES_DIR=$(SRC_DIR)/nodes
STATEMENTS_DIR=$(NODES_DIR)/statements
EXPRESSIONS_DIR=$(NODES_DIR)/expressions

all: main

$(BUILD_DIR)/main.bin: $(addprefix $(BUILD_DIR)/, main.o visitor.o IdExp.o NumExp.o OpExp.o AssignStm.o PrintStm.o CompoundStm.o)
	$(CC) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC)/main.cpp
	$(CC) -c $^ -o $@

#Visitors block
#-----------------------------------------------------------------
$(BUILD_DIR)/visitor.o: $(VISITORS_DIR)/visitor.cpp
	$(CC) -c $^ -o $@


#Expressions block
#-----------------------------------------------------------------
$(BUILD_DIR)/IdExp.o: $(EXPRESSIONS_DIR)/CIdExp.cpp
	$(CC) -c $^ -o $@

$(BUILD_DIR)/NumExp.o: $(EXPRESSIONS_DIR)/CNumExp.cpp
	$(CC) -c $^ -o $@

$(BUILD_DIR)/OpExp.o: $(EXPRESSIONS_DIR)/COpExp.cpp
	$(CC) -c $^ -o $@

#Statements block
#-----------------------------------------------------------------
$(BUILD_DIR)/AssignStm.o: $(STATEMENTS_DIR)/CAssignStm.cpp
	$(CC) -c $^ -o $@

$(BUILD_DIR)/PrintStm.o: $(STATEMENTS_DIR)/CPrintStm.cpp
	$(CC) -c $^ -o $@

$(BUILD_DIR)/CompoundStm.o: $(STATEMENTS_DIR)/CCompoundStm.cpp
	$(CC) -c $^ -o $@