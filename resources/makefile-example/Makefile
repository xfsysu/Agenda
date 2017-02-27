CC := g++ -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/functionAdd.o $(BUILD_DIR)/functionSubtract.o
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp #should use % as tongpei
	@mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDE) $< -c -o $@

clean:
	rm -f $(BUILD_DIR)/*.o #should use * as tongpei
	rm -f $(BIN_DIR)/main

#after bin has a blank so it wrong