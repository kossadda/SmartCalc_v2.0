################################################################################
#                                 _       _     _                              #
#                                (_)     | |   | |                             #
#                __   ____ _ _ __ _  __ _| |__ | | ___  ___                    #
#                \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|                   #
#                 \ V / (_| | |  | | (_| | |_) | |  __/\__ \                   #
#                  \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/                   #
#                                                                              #
#                                                                              #
################################################################################


#================================== PROJECT ===================================#
PROJECT_NAME = smartcalc
#==============================================================================#

#================================== COMPILER ==================================#
CXX = g++
#==============================================================================#

#=============================== DIRECTORY NAMES ==============================#
MAIN_DIR = ./modules
MODULES_DIR = ./modules/
TEST_DIR = ./tests
DVI_DIR = ../docs
DIST_DIR = ../dist
BUILD = ../bin
TEST_BUILD = ./test_bin
#==============================================================================#

#==================================== FLAGS ===================================#
# MAIN FLAGS FOR COMPILER
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g

# CHECK LIBRARY FOR LINKING
LDFLAGS = -lgtest -lgtest_main

# FLAGS FOR VALGRING TEST
VAL = --tool=memcheck --leak-check=yes
#==============================================================================#

#=========================== LIST OF FILE AND DIRS  ===========================#
MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
TEST_DIRS = $(shell find $(TEST_DIR) -type d)

MODULES = $(shell find $(MODULES_DIR) -type f ! -name "qcustomplot.*")
TESTS = $(shell find $(TEST_DIR) -type f")
#==============================================================================#

#======================== LIST OF FILES TO CLANG-FORMAT =======================#
ALL_FILES = $(MODULES) $(TESTS)
#==============================================================================#


################################################################################
#                      _                       _                               #
#                     | |                     | |                              #
#                    _| |_ __ _ _ __ __ _  ___| |_ ___                         #
#                   |_  __/ _` | '__/ _` |/ _ \ __/ __|                        #
#                     | || (_| | | | (_| |  __/ |_\__ \                        #
#                      \__\__,_|_|  \__, |\___|\__|___/                        #
#                                    __/ |                                     #
#                                   |___/                                      #
################################################################################


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
	@mkdir -p $(DIST_DIR)/$(PROJECT_NAME)
	@cp -r ./ $(DIST_DIR)/$(PROJECT_NAME) && rm -rf $(DIST_DIR)/$(PROJECT_NAME)/tests
	@tar -czf $(DIST_DIR)/$(PROJECT_NAME).tar.gz -C $(DIST_DIR) $(PROJECT_NAME)
	@echo "Distribution created: $(DIST_DIR)/$(PROJECT_NAME).tar.gz"
	@rm -rf $(DIST_DIR)/$(PROJECT_NAME)

test:
	mkdir -p $(TEST_BUILD)
	cd $(TEST_BUILD) && cmake ../tests && make
	valgrind $(VAL) ./$(TEST_BUILD)/tests
#==============================================================================#

#=============================== CHECKS TARGETS ===============================#
deb:
	@$(CXX) $(CXXFLAGS) -I./ ./modules/debug.cc ./modules/additional/date.cc ./modules/model/* -o test
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
