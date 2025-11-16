# Compiler and flags
CXX = g++
OPT ?= -O2
DEFINES ?=
CXXFLAGS := -std=c++17 $(OPT) -Wall $(DEFINES)

TARGET = student_program

# Source files
SRCS = main.cpp GradeCalc.cpp Student.cpp StudentIO.cpp StudentSort.cpp RuleOfThree.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Convenience targets to build with either container type
.PHONY: vector list o0 o3 vector-o0 vector-o2 vector-o3 list-o0 list-o2 list-o3

vector:
	$(MAKE) clean
	$(MAKE) DEFINES="-DUSE_VECTOR" all

list:
	$(MAKE) clean
	$(MAKE) DEFINES="-DUSE_LIST" all

o0:
	$(MAKE) clean
	$(MAKE) OPT=-O0 all

o3:
	$(MAKE) clean
	$(MAKE) OPT=-O3 all

vector-o0:
	$(MAKE) clean
	$(MAKE) OPT=-O0 DEFINES="-DUSE_VECTOR" all

vector-o2:
	$(MAKE) clean
	$(MAKE) OPT=-O2 DEFINES="-DUSE_VECTOR" all

vector-o3:
	$(MAKE) clean
	$(MAKE) OPT=-O3 DEFINES="-DUSE_VECTOR" all

list-o0:
	$(MAKE) clean
	$(MAKE) OPT=-O0 DEFINES="-DUSE_LIST" all

list-o2:
	$(MAKE) clean
	$(MAKE) OPT=-O2 DEFINES="-DUSE_LIST" all

list-o3:
	$(MAKE) clean
	$(MAKE) OPT=-O3 DEFINES="-DUSE_LIST" all