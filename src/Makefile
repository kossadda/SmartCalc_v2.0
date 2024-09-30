#================================== PROJECT ===================================#
PROJECT_NAME     =  smartcalc
#==============================================================================#

#================================== COMPILER ==================================#
CXX              =  g++
#==============================================================================#

#=============================== DIRECTORY NAMES ==============================#
TEST_DIR         =  ./tests
DVI_DIR          =  ../docs
DIST_DIR         =  ../dist
BUILD            =  ../bin
TEST_BUILD       =  ./test_bin
MAIN_DIR         =  ./main
MODEL_DIR        =  ./model
VIEW_DIR         =  ./view
CONTROLLER_DIR   =  ./controller
ADDITIONAL_DIR   =  ./additional
RESOURCES_DIR    =  ./resources
INCLUDE_DIR      =  ./include
EXCLUDE_FILE1    =  qcustomplot.*
EXCLUDE_FILE2    =  CMakeLists.txt
#==============================================================================#

#==================================== FLAGS ===================================#
CXXFLAGS         =  -Wall -Wextra -pedantic -std=c++17 -g
LDFLAGS          =  -lgtest -lgtest_main
VAL              =  --tool=memcheck --leak-check=yes
#==============================================================================#

#=========================== LIST OF FILE AND DIRS  ===========================#
ALL_MODULES_DIR  =  $(INCLUDE_DIR) $(MODEL_DIR) $(VIEW_DIR) $(CONTROLLER_DIR) $(ADDITIONAL_DIR) $(MAIN_DIR)
MODULES          =  $(shell find $(ALL_MODULES_DIR) -type f ! -name $(EXCLUDE_FILE1))
TESTS            =  $(shell find $(TEST_DIR) -type f ! -name $(EXCLUDE_FILE2))
#==============================================================================#

#======================== LIST OF FILES TO CLANG-FORMAT =======================#
ALL_FILES        =  $(MODULES) $(TESTS)
#==============================================================================#


#================================= MAIN TARGETS ===============================#
.PHONY: all install uninstall test dvi clean

all: install run

install:
	mkdir -p $(BUILD)
	cd $(BUILD) && cmake ../src && make

uninstall: clean
	rm -rf $(BUILD)

clean:
	rm -rf $(TEST_BUILD)
	rm -rf $(DIST_DIR)
	rm -rf $(DVI_DIR)
	rm -f *.txt.user

dvi:
	rm -rf $(DVI_DIR)
	doxygen ./Doxyfile
	xdg-open $(DVI_DIR)/html/index.html

dist: uninstall
	@rm -rf $(DIST_DIR)
	@echo "Creating a distribution..."
	@mkdir -p $(DIST_DIR)/$(PROJECT_NAME)/src
	@cp -r $(ALL_MODULES_DIR) $(DIST_DIR)/$(PROJECT_NAME)/src
	@cp -r $(RESOURCES_DIR) $(DIST_DIR)/$(PROJECT_NAME)/src
	@cp -r Makefile $(DIST_DIR)/$(PROJECT_NAME)/src
	@cp -r CMakeLists.txt $(DIST_DIR)/$(PROJECT_NAME)/src
	@tar -czf $(PROJECT_NAME).tar.gz -C $(DIST_DIR) $(PROJECT_NAME)
	@rm -rf $(DIST_DIR)/$(PROJECT_NAME)
	@mv $(PROJECT_NAME).tar.gz $(DIST_DIR)
	@echo "Distribution created: $(DIST_DIR)/$(PROJECT_NAME).tar.gz"

test:
	mkdir -p $(TEST_BUILD)
	cd $(TEST_BUILD) && cmake ../tests && make
	valgrind $(VAL) ./$(TEST_BUILD)/tests
#==============================================================================#

#=============================== CHECKS TARGETS ===============================#
deb:
	@$(CXX) $(CXXFLAGS) -I./ ./main/debug.cc ./additional/date.cc ./model/* -o test
	@valgrind $(VAL) ./test
	
clang_check:
	clang-format -style=Google -n $(ALL_FILES)

cpplint:
	cpplint $(ALL_FILES)

valgrind:
	valgrind $(VAL) ./$(BUILD)/$(PROJECT_NAME)
#==============================================================================#

#============================= ADDITIONAL TARGETS =============================#
run:
	@./$(BUILD)/$(PROJECT_NAME)

clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

dependencies:
	sudo apt install cmake
	sudo apt install qtbase5-dev
	sudo apt install qt6-base-dev
	sudo apt-get install libgtest-dev
	sudo apt install doxygen
	sudo apt-get install graphviz
#==============================================================================#
