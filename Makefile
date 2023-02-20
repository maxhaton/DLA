# ====================================================================================== #
#                                   From the Author                                      #
# ====================================================================================== #
# ! The purpose of this Makefile is to build the DLASystem project
# ! This makefile was adapted to work with any cpp project on OSX

# ====================================================================================== #
#                                 Variables of the Makefile                              #
# ====================================================================================== #

CXX     = g++

CXXFLAGS = -Wall -Wextra -g -O3 -march=native -flto -fno-omit-frame-pointer

IFLAGS = -I/usr/local/include -I/usr/include

LFLAGS = -L/usr/local/lib -lm -lGL -lGLU -lglut -flto

# ------------------------------------------
# FOR GENERIC MAKEFILE:
# 1 - Binary directory
# 2 - Source directory
# 3 - Executable name
# 4 - Sources names
# 5 - Dependencies names
# ------------------------------------------
BIN = .
SOURCE = .
EXEC = ./run
SOURCES = $(wildcard $(SOURCE)/*.cpp)
HEADERS = $(wildcard $(SOURCE)/*.h)
OBJECTS = $(SOURCES:.cpp=.o)

# ====================================================================================== #
#                                   Targets of the Makefile                              #
# target_name : dependency                                                               #
# <tabulation> command                                                                   #
# ====================================================================================== #

# ------------------------------------------
# ! - all : Compiles everything
# ! - help : Shows this help
# ! - clean : erases all object files *.o
# !           and all binary executables
# ------------------------------------------
all : $(BIN)/run

test: $(BIN)/hllc_test

help :
	@grep -E "^# !" Makefile | sed -e 's/# !/ /g'

clean:
	rm -f $(EXEC) $(OBJECTS)

# ------------------------------------------
# Executable
# ------------------------------------------
$(EXEC): $(OBJECTS) $(HEADERS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(IFLAGS) $(LFLAGS)

# ------------------------------------------
# Temorary files (*.o) (IFLAGS should be added here)
# ------------------------------------------
$(SOURCE)/%.o: $(SOURCE)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(IFLAGS) $(LFLAGS)







