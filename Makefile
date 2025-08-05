NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRC		= main.c parse.c utils.c init.c \
		  memory_free.c time.c routine.c \
		  threads.c philo.c watcher.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re