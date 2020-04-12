BIN_DIR = ./bin
INC_DIR = ./include
SRC_DIR = ./src
TARGET = apriori

CC = g++
CXXFLAGS = -std=c++14 -O3 -Wall

INCLUDES = -I$(INC_DIR)
LIBS =

INCS := $(wildcard $(INC_DIR)/*.h)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

$(info $(SRCS))
$(info $(OBJS))

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(INCLUDES) $(LIBS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $< $(INCLUDES) $(LIBS) -O3

clean:
	$(RM) $(BIN_DIR)/$(TARGET) $(OBJS)
