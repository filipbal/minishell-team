# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghani <ghani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 15:12:46 by fbalakov          #+#    #+#              #
#    Updated: 2025/02/12 23:00:00 by ghani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRCS        = srcs/main.c srcs/parser/lexer.c

OBJS        = $(SRCS:.c=.o)

LIBFT       = libft
LIBFT_A     = $(LIBFT)/libft.a

INCLUDES    = -I./includes -I./$(LIBFT)
LFLAGS      = -lreadline

all:        $(NAME)

$(LIBFT_A):
			make -C $(LIBFT)

$(NAME):    $(LIBFT_A) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LFLAGS) -o $(NAME)

%.o:        %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
			make clean -C $(LIBFT)
			$(RM) $(OBJS)

fclean:     clean
			make fclean -C $(LIBFT)
			$(RM) $(NAME)

re:         fclean all

.PHONY:     all clean fclean re