CC= gcc
SRC_PATH = .
SRC_EXT = c
BUILD_PATH = ../../build/netlib

LIB_NAME= netlib.a

SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

DEPS = $(OBJECTS:.o=.d)

INCLUDES = -I ./include

.PHONY: all
all: dir $(BUILD_PATH)/$(LIB_NAME)
	@echo "Start compiling netlib"
	@echo $(OBJECTS)

dir:
	@mkdir -p ../../build
	@mkdir -p ../../build/netlib

-include $(DEPS)

# Creation of the executable
$(BUILD_PATH)/$(LIB_NAME): $(OBJECTS)
	@echo "Building library: $@"
	ar rcs $@ $^

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ../../build/netlib
