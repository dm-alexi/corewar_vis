NAME = corewar
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEAD_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEAD_DIR = $(LIBFT_DIR)/include
LDFLAGS = -I $(HEAD_DIR) -I $(LIBFT_HEAD_DIR)
HEAD_FILES = corewar.h op.h visualizer.h
SRC_FILES = main.c error.c input.c arena.c battle.c delete.c op1.c op2.c op3.c op4.c output.c players.c process.c table.c vmodule.c \
	choose_colors_pt1.c choose_colors_pt2.c push_info.c push_info_pt2.c visualizer.c visualizer_help_pt2.c visualizer_help.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# OS detection.
ifeq ($(OS),Windows_NT)
	detected_OS = Windows
else
	detected_OS = $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif
# Note: Current version only supports Linux and Mac OS.
ifeq ($(detected_OS),Darwin)
	FRAMEWORKS = -framework SDL2 -framework SDL2_ttf
	FLAGS += -F ~/Library/Frameworks 
	LDFLAGS += -I ~/Library/Frameworks/SDL2.framework/Headers -I ~/Library/Frameworks/SDL2_ttf.framework/Headers
else
	FRAMEWORKS = -lSDL2 -lSDL2_ttf
endif

all: $(NAME)

-include $(OBJ:.o=.d)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FRAMEWORKS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(LDFLAGS) -o $@ -c $< -MMD

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT): FAKE
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re FAKE
