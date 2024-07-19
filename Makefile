PROJECT_NAME = intersection
# commands
CC = g++
RM := rm -rf
MKDIR := mkdir -p
# flag and parameters
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS= -std=c++17 -O2 -lstdc++
LINUX_FLAGS =-lrt -lpthread -lm
GCOV_FLAGS =--coverage
TEST_FLAGS = -lgtest
# paths and filenames
TEST_DIR = tests
SRC_DIR = src
TEST_FILES = $(TEST_DIR)/test_*.cc
C_FILES = $(SRC_DIR)/*.cc
H_FILES = $(SRC_DIR)/*.h
TEST_TARGET = testing
REPORTS = reports

all: test

test: $(TEST_NAME)
	 $(CC) $(CFLAGS) $(CPPFLAGS) $(C_FILES) $(TEST_FILES) $(TEST_FLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: 
	$(CC) $(GCOV_FLAGS) $(CPPFLAGS) $(C_FILES) $(TEST_FILES) -o $(TEST_TARGET) $(TEST_FLAGS)
	./$(TEST_TARGET)
	@$(MKDIR) $(REPORTS)
	lcov -t "test" -o test.info -c -d ./ --no-external
	genhtml -o $(REPORTS) test.info
	$(OPEN_CMD) ./report/index.html

clean:
	@rm -f $(TEST_TARGET)
	@$(RM) $(BUILD_DIR) $(REPORTS)
	@$(RM) *.o *.out *.info *.gcda *.gcno
	@echo "-- All clean"

style:
	cd ./$(SRC_DIR)/; clang-format -n -style=google *.h *.cc
	cd ./$(TEST_DIR)/; clang-format -n -style=google *.cc

format:
	cd ./$(SRC_DIR)/; clang-format -i -style=google *.h *.cc
	cd ./$(TEST_DIR)/; clang-format -i -style=google *.cc

.PHONY: all clean test gcov_report style format
