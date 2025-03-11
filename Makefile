NAME = cub3d

LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

MLX_PATH = ./mlx/
MLX_LIB = $(addprefix $(MLX_PATH), $(MLX_NAME))

SRC = srcs/main.c srcs/check.c srcs/check1.c srcs/sprites.c srcs/player_pos.c srcs/render.c

OBJS := $(SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -g3
MLX_FLAGS = -Lmlx -lmlx_Linux -Imlx -lXext -lX11

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	make -sC $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)

clean:
	make clean -sC $(LIBFT_PATH)
	make clean -sC $(MLX_PATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re