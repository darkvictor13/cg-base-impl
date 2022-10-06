CXX=g++
CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -I ../include -I ../src -I ../src/view -I ../src/draw_elements
#-fsanitize=address -pedantic
#LDFLAGS=-fsanitize=address
LIBFLAGS=-lm

WX_CONFIG := wx-config
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

CXXFLAGS+=$(WX_CXXFLAGS)
LIBFLAGS+=$(WX_LIBS)

OBJ_DIR=./objs
SRC_DIR=../src

EXEC=main.out
SRC := $(wildcard $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

debug: CXXFLAGS += -g -DDEBUG_BUILD
debug: $(EXEC)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBFLAGS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(EXEC) $(OBJ)

run: $(EXEC)
	./$(EXEC)