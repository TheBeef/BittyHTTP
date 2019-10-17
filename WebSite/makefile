CC = gcc
CC_FLAGS = -fno-builtin-printf -std=gnu99 -g --short-enums -Wall -fmax-errors=1 -Wfatal-errors
LNK_FLAGS =

# Final binary
BIN = website.exe

# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

SOURCE_DIR = src

# List of all .c source files.
SOURCE = Base/main.c \
	Base/FileServer.c \
	Base/SocketsCon.c \
	Base/WebServer.c \
	Base/TimeStamp.c \
	Common/Headers.c \
	Common/CommonCSS.c \
	Common/DownloadInfo.c \
	CodeExamples.c \
	../../ReleaseNotes.c \
	Pages/Root.c \
	Pages/About.c \
	Pages/Development.c \
	Pages/Links.c \
	Pages/Contact.c \
	Pages/FAQ.c \
	Pages/License.c \
	Pages/Download.c \
	Pages/AutoDocs.c \
	Pages/DisplayReleaseNotes.c \
	Pages/StatInfo.c \
	Pages/Doc/TheBasics.c \
	Pages/Doc/HelloWorld.c \
	Pages/Doc/CSS.c \
	Pages/Doc/Graphics.c \
	Pages/Doc/DynamicContent.c \
	Pages/Doc/GETVars.c \
	Pages/Doc/POSTVars.c \
	Pages/Doc/Cookies.c \
	Pages/Doc/Headers.c \
	Pages/Doc/URLEncoding.c \
	Pages/Doc/Waiting.c \
	Pages/Doc/Error404.c \

INCLUDES = src

.PHONY: PreBuild

# All .o files go to build dir.
OBJ = $(SOURCE:%.c=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)
# Include paths with a -I in front of them
CC_INCLUDE = $(INCLUDES:%= -I %)

# Default target named after the binary.
$(BIN) : $(BUILD_DIR)/$(BIN)

PreBuild:
	-rm $(BUILD_DIR)/Base/TimeStamp.o || true

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/$(BIN) : PreBuild $(OBJ)
	echo Linking...
	# Create build directories - same structure as sources.
	mkdir -p $(@D)
	# Just link all the object files.
	$(CC) $(CC_FLAGS) $(OBJ) $(LNK_FLAGS) -o $@
	-cp $(BUILD_DIR)/$(BIN) $(BIN)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	echo Compiling $(notdir $<)
	mkdir -p $(@D)
	# The -MMD flags additionaly creates a .d file with
	# the same name as the .o file.
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -MMD -c $< -o $@

#.PHONY : clean
clean :
	# This should remove all generated files.
	-rm $(BUILD_DIR)/$(BIN) $(OBJ) $(DEP)
