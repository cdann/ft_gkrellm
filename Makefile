NAME = ft_gkrellm

CC = g++ -Wall -Wextra -Werror

SRC += src/collector/ACollector.cpp
SRC += src/collector/TimeColl.cpp
SRC += src/collector/UserHostColl.cpp
SRC += src/collector/OsInfoColl.cpp
SRC += src/collector/CpuColl.cpp

SRC += src/display/AMonitorDisplay.cpp
SRC += src/display/GTKDisplay.cpp
SRC += src/display/Debug_Display/DebugDisplay.cpp

SRC += src/mod/AModule.cpp
SRC += src/mod/TimeMod.cpp
SRC += src/mod/UseHostMod.cpp
SRC += src/mod/OsInfoMod.cpp
SRC += src/mod/CpuMod.cpp

SRC += src/main.cpp

INCLUDES = -Iincludes
LIBS = -lncurses `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`

OBJ = $(subst .cpp,.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -O3 -o $(NAME) $(OBJ) $(INCLUDES) $(LIBS)

%.o:%.cpp
	@$(CC) -O3 -c -o $@ $^ $(INCLUDES) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

init:
	export PKG_CONFIG_PATH=/usr/X11/lib/pkgconfig

