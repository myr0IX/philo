# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macassag <macassag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 08:54:43 by macassag          #+#    #+#              #
#    Updated: 2024/03/05 10:25:48 by macassag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

# DFLAGS = -fsanitize=thread -pthread 
CFLAGS = -pthread -Wall -Wextra -Werror -I 

INCS		=	includes
SRC_DIR		=	./src
OBJ_DIR		=	.obj

SRC 		=	exit_file.c \
				ft_atoi.c \
				init_philo.c \
				main.c \
				philo.c

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