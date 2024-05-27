# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macassag <macassag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 08:54:43 by macassag          #+#    #+#              #
#    Updated: 2024/05/19 12:17:18 by macassag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

# DFLAGS = -fsanitize=thread -pthread 
CFLAGS = -pthread -g3 -Wall -Wextra -Werror -I 

INCS		=	includes
SRC_DIR		=	./src
OBJ_DIR		=	.obj

SRC 		=	bool.c  ft_atoi.c  main.c  monitor.c  mutex.c \
				philo.c  print_log.c  time.c  utils.c	debug.c

OBJ			=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HEADERS		=	$(addprefix $(INCS)/,philo.h)
NAME		=	philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all