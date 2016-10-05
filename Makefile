CC := clang++
CXX := clang++
CCFLAGS := -O3 -march=native
CXXFLAGS := -O3 -march=native
CPPFLAGS := -std=c++11 -I./include

TARGET_ARCH := -m64

LDFLAGS := -lboost_program_options-mt -lboost_filesystem-mt -lboost_system-mt

VPATH := ./src ./include

MAINFILE := main.cpp
EXEC := $(MAINFILE:%.cpp=%)

SRC := $(wildcard src/*.cpp)
SRC := $(SRC:src/%=%)
OBJ := $(SRC:%.cpp=%.o)

$(EXEC) : $(OBJ)

.PHONY : clean veryclean

clean :
	$(RM) -vf $(OBJ)

veryclean : clean
	$(RM) -vf $(EXEC)
