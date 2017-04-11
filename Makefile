CC = g++

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep
BUILD_PATH = build

LINK_FLAGS = 
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d
DIRECTIVES = -std=c++11 -Wall -Wextra -c -I$(INC_PATH) -Dmain=SDL_main -fdiagnostics-color -m64
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -Dmain=SDL_main

EXEC = $(BUILD_PATH)/Jogo

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

ifeq ($(OS),Windows_NT)

RMDIR = rd /s /q
RM = del

SDL_PATH = C:/tools/msys64/mingw64

DIRECTIVES += -I$(SDL_PATH)/include/SDL2 -mwindows --machine-windows

LIBS += -L$(SDL_PATH)/lib -lSDL2main -lmingw32 -mwindows --machine-windows

EXEC := $(EXEC).exe

else

RMDIR = rm -rf
RM = rm -f

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)

LIBS = -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf -lm

endif
endif

PRE_FLAGS = -DPROJECT_VERSION_MAJOR=2\
			-DPROJECT_VERSION_MINOR=0\
			-DPROJECT_VERSION_PATCH=0\
			-DPROJECT_VERSION_TWEAK=0

.PRECIOUS: $(DEP_PATH)/%.d
.PHONY: debug clean release profile

print-%: ; @echo $* = $($*)

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS) $(LINK_FLAGS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
	@if not exist $(BUILD_PATH) @mkdir $(BUILD_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif
	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES) $(PRE_FLAGS)

clean:
ifeq ($(OS),Windows_NT)
	@if exist $(DEP_PATH) $(RMDIR) $(DEP_PATH)
	@if exist $(BIN_PATH) $(RMDIR) $(BIN_PATH)
	@if exist $(BUILD_PATH) $(RMDIR) $(BUILD_PATH)
else
	$(RMDIR) $(BIN_PATH) $(DEP_PATH) $(BUILD_PATH)
endif
#	 $(RM) $(EXEC)

-include $(DEP_FILES)

debug:
ifeq ($(OS),Windows_NT)
	DIRECTIVES += -mconsole
	LIBS += -mconsole
endif
DIRECTIVES += -ggdb -O0 -DDEBUG=1
debug: all

profile:
	DIRECTIVES += -pg --coverage -O0 -DDEBUG=0
	LINK_FLAGS += -pg --coverage
profile: all

release:
	DIRECTIVES += -Ofast -mtune=native -DDEBUG=0
release: all

#copy-dlls:
#ifeq ($(OS))
