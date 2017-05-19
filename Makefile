CC = g++

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep
BUILD_PATH = build

DEBUG = 0

LINK_FLAGS = 
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d
DIRECTIVES = -std=c++11 -Wall -Wextra -I$(INC_PATH) -fdiagnostics-color -m64 -DDEBUG=$(DEBUG)
LIBS = -lm -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

EXEC = $(BUILD_PATH)/Jogo

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

ifeq ($(OS),Windows_NT)
RMDIR = rd /s /q
RM = del

SDL_PATH = C:/tools/msys64/mingw64
INC_PATH += -I$(SDL_PATH)/include/SDL2

DIRECTIVES += -mwindows -Dmain=SDL_main
LIBS := -L$(SDL_PATH)/lib -lmingw32 -lSDL2main $(LIBS)
EXEC := $(EXEC).exe

else
RMDIR = rm -rf
RM = rm -f

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
LIBS = -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif

endif

PRE_FLAGS = -DPROJECT_VERSION_MAJOR=6\
			-DPROJECT_VERSION_MINOR=0\
			-DPROJECT_VERSION_PATCH=1\
			-DPROJECT_VERSION_TWEAK=2

.PRECIOUS: $(DEP_PATH)/%.d
.PHONY: debug clean release profile coverage

print-%: ; @echo $* = $($*)

release: set_release all

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS) $(LINK_FLAGS)
	@echo Done! Compiled game is in the $(BUILD_PATH) folder

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
	@if not exist $(BUILD_PATH) @mkdir $(BUILD_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(BUILD_PATH)
endif
	@$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES) $(PRE_FLAGS)

clean:
ifeq ($(OS),Windows_NT)
	@if exist $(DEP_PATH) $(RMDIR) $(DEP_PATH)
	@if exist $(BIN_PATH) $(RMDIR) $(BIN_PATH)
	@if exist $(BUILD_PATH) $(RMDIR) $(BUILD_PATH)
else
	@$(RMDIR) $(BIN_PATH) $(DEP_PATH) $(BUILD_PATH)
endif

-include $(DEP_FILES)

debug: set_debug all
set_debug:
ifeq ($(OS),Windows_NT)
	$(eval DIRECTIVES += -mconsole)
	$(eval LIBS += -mconsole)
endif
	$(eval DIRECTIVES += -ggdb3 -O0)
	$(eval DEBUG = 1)

profile: set_profile all
set_profile:
	$(eval DIRECTIVES += -pg)
	$(eval LINK_FLAGS += -pg)

coverage: set_coverage all
set_coverage:
	$(eval DIRECTIVES += --coverage -O0)
	$(eval LINK_FLAGS += --coverage)

set_release:
	$(eval DIRECTIVES += -Ofast -mtune=native)

help:
	@echo.
	@echo Available targets:
	@echo - release:  Builds the release version (default target)
	@echo - debug:    Builds the debug version
	@echo - profile:  Builds a version to use with gprof
	@echo - coverage: Builds a version to use with gcov
	@echo - help:     Shows this help
	@echo.
