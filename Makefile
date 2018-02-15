# About:
# 	This Makefile will handle header dependencies and objects for you. Just run make
#
# Usage:
# 	- Your main source code should go in a folder called 'src'
# 	- Set the variables below
# 	- Objects will be output to /build/src/ and the binary to /build/TARGET_EXEC


###  Modify these values for your project ###

TARGET_EXEC ?= tmxjson.so

# Add your -IDIRS here. Dont include the -I part as it will be done for you
MY_INC_DIRS = 

# Add your linking flags here
MY_LDFLAGS =

### END ###


### You can leave the below values alone ###

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) $(MY_INC_DIRS)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++14 -O2 -Wall -Wextra

LDFLAGS = $(MY_LDFLAGS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

### END ###
