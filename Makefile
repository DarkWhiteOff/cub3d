NAME = cub3D
NAME_BONUS = $(NAME)_bonus

LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

MLX_PATH = ./mlx/
MLX_LIB = $(addprefix $(MLX_PATH), $(MLX_NAME))

SRC = srcs/color1.c srcs/render1.c srcs/main.c srcs/check.c srcs/check1.c srcs/check2.c srcs/check3.c srcs/player_pos.c srcs/render.c srcs/utils.c srcs/init.c srcs/color.c srcs/free.c srcs/utils1.c srcs/key.c

SRC_BONUS = $(addprefix srcs_bonus/, \
	check_bonus.c check1_bonus.c check2_bonus.c check3_bonus.c \
	color_bonus.c free_bonus.c init_bonus.c \
	main_bonus.c player_pos_bonus.c render_bonus.c \
	utils_bonus.c utils1_bonus.c key_bonus.c render1_bonus.c \
	color1_bonus.c)

OBJS := $(SRC:.c=.o)

OBJS_BONUS := $(SRC_BONUS:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -g3
MLX_FLAGS = -Lmlx -lmlx_Linux -Imlx -lXext -lX11 -lm


all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	make -sC $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT_LIB) $(OBJS_BONUS)
	make -sC $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(DEP_BONUS) $(LIBFT_LIB) -o $(NAME_BONUS) -L$(MLX_PATH) $(MLX_FLAGS)

clean:
	make clean -sC $(LIBFT_PATH)
	make clean -sC $(MLX_PATH)
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re