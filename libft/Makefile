# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 14:24:43 by zamgar            #+#    #+#              #
#    Updated: 2025/03/19 13:56:07 by tzizi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_strncmp.c \
	ft_printf.c \
	ft_hex.c \
	ft_itoa.c \
	ft_ptr.c \
	ft_putcharstr.c \
	ft_strlen.c \
	ft_unsigned_itoa.c \
	get_next_line.c \
	get_next_line_utils.c

BFILES =	ft_strncmp.o \
		ft_printf.o \
		ft_hex.o \
		ft_itoa.o \
		ft_ptr.o \
		ft_putcharstr.o \
		ft_strlen.o \
		ft_unsigned_itoa.o \
		get_next_line.o \
		get_next_line_utils.o

OBJS = ${SRC:.c=.o}

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
