# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 20:42:57 by gasouza           #+#    #+#              #
#    Updated: 2024/04/07 21:54:06 by gasouza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= RPN
SRCS		= main.cpp RPN.cpp

COMPILER 	= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98 -O3
CLEANUP		= rm -rf


all: $(NAME)

$(NAME): $(SRCS)
	$(COMPILER) $^ $(CFLAGS) -o $@

clean:
	$(CLEANUP) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re