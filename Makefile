# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/04 15:10:01 by tle-huu-          #+#    #+#              #
#    Updated: 2018/02/04 15:38:41 by tle-huu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
FRAMEWORK = -framework OpenGl -framework Appkit
INCLUDES = includes/
LIBFT = lib/libftprintf.a
GCC = gcc -Wall -Werror -Wextra -g3
SRCS =	srcs/dda.c		\
		srcs/game.c		\
		srcs/init.c		\
		srcs/motion.c	\
		srcs/parser.c	\

LIB = libzer/ -lmlx -lftprintf
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)
	@cp $(LIBFT) libzer/
	@$(GCC) -I$(INCLUDES) $(SRCS) -L $(LIB) $(FRAMEWORK) -o $(NAME)
	@printf "\r\033[K[WOLF3D] \033[0;32mWolf3d ready to roll ! \033[0m"


$(LIBFT):
	@make -C lib/

clean:
	@make -C lib/ clean
	@rm -f $(OBJS)
	@printf "[WOLF3D] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@make -C lib/ fclean
	@rm -f $(NAME)
	@rm -f libzer/libftprintf.a
	@printf "[WOLF3D] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
