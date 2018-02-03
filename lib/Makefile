# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/19 10:53:51 by tle-huu-          #+#    #+#              #
#    Updated: 2018/01/24 21:37:16 by tle-huu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = init.c						\
	   parser.c						\
	   ft_printf.c						\
	   ft_print_specifier.c	\
	   print_hex.c			\
	   print_mhex.c			\
	   print_string.c			\
	   print_char.c			\
	   print_obelus.c			\
	   print_integer.c		\
	   print_unsint.c			\
	   print_bigunsint.c			\
	   print_linteger.c		\
	   print_pointer.c		\
	   print_wstring.c		\
	   print_oct.c			\
	   handle_h.c			\
	   handle_l.c			\
	   handle_j.c			\
	   handle_z.c			\
	   handle_size.c		\

CFLAGS =-g3 -c -Wall -Wextra -Werror
FLAGS  = -g3 -Wall -Wextra -fsanitize=address
TEST = printf
INCLUDES = ft_printf.h
CC = gcc
LN = ar
LFLAGS = rc
LIBOPTIMIZER = ranlib
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "\r\033[K[PRINTF] \033[0;32mLinking...\033[0m"
	@cp $(LIBFT) $(NAME)
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "\r\033[K[PRINTF] \033[0;32mDone!\033[0m\n"

$(LIBFT):
	@$(MAKE) -C libft/

%.o: %.c
	@printf "\r\033[K[PRINTF] \033[0;32mBuilding $<\033[0m"
	@$(CC) $(CFLAGS) $< -o $@


clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJS)
	@printf "[PRINTF] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)
	@printf "[PRINTF] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
	# **************************************************************************** #
