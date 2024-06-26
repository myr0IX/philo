CC = cc

CFLAGS = -pthread -g3 -Wall -Wextra -Werror -I 

INCS		=	includes
SRC_DIR		=	./src
OBJ_DIR		=	.obj

SRC 		=	bool.c  ft_atoi.c  main.c  monitor.c  mutex.c \
				philo.c  print_log.c  time.c  utils.c	utils2.c

OBJ			=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HEADERS		=	$(addprefix $(INCS)/,philo.h)
NAME		=	philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all