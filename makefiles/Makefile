SRC_DIR=src
BUILD_DIR=build
VISITORS_DIR=$(SRC_DIR)/visitors
NODES_DIR=$(SRC_DIR)/nodes
STATEMENTS_DIR=$(NODES_DIR)/statements
EXPRESSIONS_DIR=$(NODES_DIR)/expressions
CFLAGS=-std=c++11

all: $(BUILD_DIR)/main.bin

$(BUILD_DIR)/main.bin: $(addprefix $(BUILD_DIR)/, main.o IdExp.o NumExp.o OpExp.o AssignStm.o PrintStm.o CompoundStm.o PrintResults.o PrintVisitor.o CalculateResults.o CaculateVisitor.o)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#Visitors block
#-----------------------------------------------------------------
$(BUILD_DIR)/PrintResults.o: $(VISITORS_DIR)/CPrintResults.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/PrintVisitor.o: $(VISITORS_DIR)/CPrintVisitor.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/CalculateResults.o: $(VISITORS_DIR)/CalculateResults.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/CaculateVisitor.o: $(VISITORS_DIR)/CaculateVisitor.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#Expressions block
#-----------------------------------------------------------------
$(BUILD_DIR)/IdExp.o: $(EXPRESSIONS_DIR)/CIdExp.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/NumExp.o: $(EXPRESSIONS_DIR)/CNumExp.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/OpExp.o: $(EXPRESSIONS_DIR)/COpExp.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#Statements block
#-----------------------------------------------------------------
$(BUILD_DIR)/AssignStm.o: $(STATEMENTS_DIR)/CAssignStm.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/PrintStm.o: $(STATEMENTS_DIR)/CPrintStm.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/CompoundStm.o: $(STATEMENTS_DIR)/CCompoundStm.cpp
	$(CC) $(CFLAGS) -c $^ -o $@


clean:
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)/*.bin