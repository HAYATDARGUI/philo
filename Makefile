SRC=parsing_philo.c philo.c routine.c time.c init_data.c print_action.c

OBJ=$(SRC:.c=.o)

CC=gcc

CFLAGS=-Wall -Wextra -Werror -pthread
NAME=philo
all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re