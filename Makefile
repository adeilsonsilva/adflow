#############
# Variables #
#############
CXX = g++

CXXFLAGS = -std=c++14 -O3 -ffast-math

LDFLAGS= -lm

INCLUDE = -I include

BUILD = build

SRC = src

###########
# Scripts #
###########
dir:
	@mkdir -p $(BUILD) $(BUILD)/types

all: dir main.out

###########
# Objects #
###########
$(BUILD)/types/vector.o: $(SRC)/types/vector.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

$(BUILD)/types/matrix.o: $(SRC)/types/matrix.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

$(BUILD)/types/tensor.o: $(SRC)/types/tensor.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

$(BUILD)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

###############
# Executables #
###############
main.out: $(BUILD)/main.o $(BUILD)/types/vector.o $(BUILD)/types/matrix.o $(BUILD)/types/tensor.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

##########
# Clean #
##########
clean:
	@rm -f $(BUILD)/*.o *.out
