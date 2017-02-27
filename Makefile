CC := g++ -std=c++11 -w
BIN_DIR := bin
BUILD_DIR := build
DATA_DIR := data
INC_DIR := include
SRC_DIR := src
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/gtest-sample-for-Agenda.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/User.o #add other needed *.o file is OK
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ -g $(INCLUDE) -I./gtest-1.6.0/include -L./gtest-1.6.0/lib/.libs -Wl,-rpath=./gtest-1.6.0/lib/.libs -lgtest -lgtest_main -lpthread 
$(BUILD_DIR)/gtest-sample-for-Agenda.o: $(SRC_DIR)/gtest-sample-for-Agenda.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $< -c -o $@ -g $(INCLUDE) -I./gtest-1.6.0/include -L./gtest-1.6.0/lib/.libs -Wl,-rpath=./gtest-1.6.0/lib/.libs -lgtest -lgtest_main -lpthread

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDE) $< -c -o $@ -g

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)