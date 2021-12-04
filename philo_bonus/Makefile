NAME = philo_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

SRCS = philosophers.c\
			living.c\
			philo_utils.c\
			creating_processes.c

HEADERS = philosophers_bonus.h

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: ann clean fclean re