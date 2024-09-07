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
LIBRARY = $(PROJECT_NAME).a
#==============================================================================#

#================================== COMPILER ==================================#
CXX = g++
#==============================================================================#

#=============================== DIRECTORY NAMES ==============================#
OBJ_DIR = ./obj
MODULES_DIR = ./modules
TEST_DIR = ./tests
REPORT_DIR = ./report
DVI_DIR = ./../docs
DIST_DIR = ./../dist
#==============================================================================#

#==================================== FLAGS ===================================#
# MAIN FLAGS FOR COMPILER
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -std=c++17

# CHECK LIBRARY FOR LINKING
LDFLAGS = -lgtest -lgtest_main

# CHECK & GCOV LIBRARY FOR LINKING
LDGCOV = $(LDFLAGS) -lgcov

# FLAGS FOR COVERING MODULES
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# FLAGS FOR VALGRING TEST
VAL = --tool=memcheck --leak-check=yes
#==============================================================================#


#================================ MAIN HEADER =================================#
MAIN_H = $(shell find ./ -maxdepth 1 -name "*.h")
#==============================================================================#


#====================== LIST OF FILE AND DIRS IN MODULES ======================#
MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
MODULES_CC = $(shell find $(MODULES_DIR) -type f -name "*.cc")
MODULES_H = $(shell find $(MODULES_DIR) -type f -name "*.h")
MODULES_O = $(notdir $(MODULES_CC:%.cc=%.o))
MODULES_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(MODULES_O))
#==============================================================================#


#==================== LIST OF FILE AND DIRS IN TEST MODULES ===================#
TEST_DIRS = $(shell find $(TEST_DIR) -type d)
TEST_CC = $(shell find $(TEST_DIR) -type f -name "*.cc")
TEST_H = $(shell find $(TEST_DIR) -type f -name "*.h")
TEST_O = $(notdir $(TEST_CC:%.cc=%.o))
TEST_OBJ_PATH = $(OBJ_DIR)/*_test.o
#==============================================================================#


#======================== LIST OF FILES TO CLANG-FORMAT =======================#
ALL_FILES = $(MODULES_CC) $(TEST_CC) $(MODULES_H) $(MAIN_H) $(TEST_H)
#==============================================================================#


#=============== CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS ===============#
vpath %.cc $(MODULES_DIRS) : $(TEST_DIRS)
vpath %.o $(OBJ_DIR)
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
.PHONY: test

all: dvi test

$(LIBRARY): $(OBJ_DIR) $(MODULES_O) $(MODULES_H) $(MAIN_H)
	ar rcs $@ $(addprefix $(OBJ_DIR)/, $(notdir $(MODULES_O)))
	ranlib $@

test: clean $(LIBRARY)
	@$(CXX) $(TEST_CC) $(LIBRARY) $(LDFLAGS) -o $@
	@-./$@

dvi:
	rm -rf $(DVI_DIR)
	doxygen Doxyfile
	xdg-open $(DVI_DIR)/html/index.html

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -rf $(DVI_DIR)
	rm -rf gcov_report
	rm -f test
	rm -f *.a *.o
	rm -f *.gc*
	rm -f val.txt

rebuild: clean all
#==============================================================================#


#============================== CREATE DIRECTORIES ============================#
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
#==============================================================================#


#============================== OBJECTIVE TARGETS =============================#
%.o: %.cc ${MODULES_H}
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) -c -o $(addprefix ${OBJ_DIR}/, $@) $<

%_test.o: %_test.cc
	$(CXX) $(CXXFLAGS) -c -o $(addprefix ${OBJ_DIR}/, $@) $<
#==============================================================================#


#=============================== CHECKS TARGETS ===============================#
deb:
	@$(CXX) -Wall -Wextra -pedantic -g -std=c++17 ./debug/debug.cc $(MODULES_CC) -o test
	@valgrind $(VAL) ./test
	
clang_check:
	clang-format -style=Google -n $(ALL_FILES)

cpplint:
	cpplint $(ALL_FILES)

valgrind: test
	$@ $(VAL) ./test
#==============================================================================#


#============================= ADDITIONAL TARGETS =============================#
clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

dependencies:
	sudo apt-get install libgtest-dev
	sudo apt install doxygen
	sudo apt-get install graphviz
#==============================================================================#