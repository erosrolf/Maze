PROJECT_NAME = A1_Maze_CPP

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	OPEN_CMD = xdg-open
	QTFLAGS = CONFIG+=qtquickcompiler
	RUNINSTR= ./build/$(NAME_PROJECT).app
endif
ifeq ($(UNAME), Darwin)
	OPEN_CMD = open
	LCOV_FLAG = --ignore-errors inconsistent
	QTFLAGS = -spec macx-clang CONFIG+=qtquickcompiler
	RUNINSTR= open build/$(NAME_PROJECT).app
endif

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g --coverage
LDFLAGS = -lgtest -lgtest_main -pthread
LCOV = lcov
LCOV_FLAGS = --ignore-errors inconsistent --ignore-errors mismatch
GENHTML = genhtml
COVERAGE_DIR = $(DIR_BUILD)/coverage

DIR_BUILD = ./build
DIR_VIEW = ./src/view
DIR_CORE = ./src/core
DIR_OBJ = ./obj
DIR_TESTS = ./tests

CORE_LIB = $(DIR_BUILD)/$(PROJECT_NAME)_core_lib.a

SRC = $(shell find $(DIR_CORE) -type f -name '*.cc')
OBJ = $(SRC:$(DIR_CORE)/%.cc=$(DIR_OBJ)/%.o)
TEST_SRC = $(shell find $(DIR_TESTS) -type f -name '*.cc')
TEST_OBJ = $(TEST_SRC:$(DIR_TESTS)/%.cc=$(DIR_OBJ)/%.o)
TEST_EXECUTABLE = $(DIR_BUILD)/core_test

all: core_lib core_test

run:
	cd $(DIR_BUILD) && ./Maze

install:
	mkdir -p $(DIR_BUILD)
	cp -r resources $(DIR_BUILD)/resources
	cd $(DIR_BUILD) && cmake .. && make -j4

# BUILD CORE LIB
core_lib: $(CORE_LIB)
$(CORE_LIB): $(OBJ)
	@mkdir -p $(DIR_BUILD)
	ar rcs $@ $(OBJ)
	@ranlib $@

$(DIR_OBJ)/%.o: $(DIR_CORE)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# BUILD CORE TESTS
tests: clean core_test
core_test: $(TEST_EXECUTABLE)
	@./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(OBJ) $(TEST_OBJ)
	@mkdir -p $(DIR_BUILD)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(DIR_OBJ)/%.o: $(DIR_TESTS)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

gcov_report: tests
	@lcov -o test.info --no-external -c -d . $(LCOV_FLAG) --ignore-errors mismatch
	@genhtml -o report test.info $(LCOV_FLAG)
	@rm -rf *.gcda *.gcno *.info *.dSYM
	$(OPEN_CMD) report/index.html

dist:
	git archive --format=tar --prefix=$(NAME_PROJECT)/ HEAD | gzip > $(PROJECT_NAME).tgz

dvi:
	doxygen Doxyfile
	$(OPEN_CMD) ./documentation/html/index.html

valgrind: tests
	@CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TEST_EXECUTABLE)

style_check:
	@find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n -style=Google {}'

style_repair: clean
	@find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -i -style=Google {}'

clean:
	rm -rf build
	rm -rf report test.info
	rm -rf obj
