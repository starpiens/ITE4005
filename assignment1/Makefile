BIN_DIR = ./bin
INC_DIR = ./include
SRC_DIR = ./src

CC = g++
CFLAGS = -std=c++14 -g -Wall -O3

INCLUDES = -I$(INC_DIR)
LIBS = -lpthread -lm

INCS := $(wildcard $(INC_DIR)/*.h)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.c=.o)

apriori: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/apriori $(OBJS) $(INCLUDES) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(BIN)$(TARGET) $(OBJS)