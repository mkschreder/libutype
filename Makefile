BUILD_DIR=build_dir
STATIC_LIB=$(BUILD_DIR)/libutype.a
SHARED_LIB=$(BUILD_DIR)/libutype.so 
SOURCES=\
	src/avl-cmp.c \
	src/avl.c \
	src/kvlist.c \
	src/safe_list.c \
	src/utils.c \
	src/vlist.c 
INSTALL_PREFIX:=/usr

OBJECTS=$(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SOURCES)))

CFLAGS+=-I. -fPIC -Wall -Werror -std=gnu99

all: $(BUILD_DIR) $(STATIC_LIB) $(SHARED_LIB) 

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

$(SHARED_LIB): $(OBJECTS) 
	$(CC) -shared -Wl,--no-undefined -o $@ $^ -ldl

$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs -o $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

install: 
	mkdir -p $(INSTALL_PREFIX)/include/libutype
	cp -R src/*.h $(INSTALL_PREFIX)/include/libutype/
	mkdir -p $(INSTALL_PREFIX)/lib/
	cp -R $(SHARED_LIB) $(STATIC_LIB) $(INSTALL_PREFIX)/lib/

clean: 
	rm -rf build_dir
	rm -f examples/*.o
