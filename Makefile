#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 10:38:16 by rdestreb          #+#    #+#              #
#    Updated: 2015/01/21 19:46:01 by rdestreb         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol
SRCDIR = ./src
HEADDIR = ./src
HEAD = fdf.h
HEADFILES = $(addprefix $(HEADDIR)/, $(HEAD))
SCRFILES = $(addprefix $(SRCDIR)/, $(SRC))
SRC =	main.c \
		mlx.c \
		image.c \
		fractal.c \
		tools.c \
		hook.c

OBJS = $(SCRFILES:.c=.o)
CC = gcc
CFLAGS = -O3 -Wall -Werror -Wextra
LDFLAGS = -L ./libft/ -lft -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C ./libft/

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C ./libft/ $@
	/bin/rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./libft/ $@
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
