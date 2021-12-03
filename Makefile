NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread
# -Wall -Wextra -Werror

MAIN_SRCS = philosophers.c\
			living.c\
			philo_utils.c

BONUS_SRCS = philosophers.c\
			living.c\
			philo_utils.c\
			creating_processes.c

HEADERS = philosophers.h

SRCS = $(addprefix ./philos/, $(MAIN_SRCS))
B_SRCS = $(addprefix ./philo_bonus/, $(BONUS_SRCS))

OBJS = $(SRCS:c=o)
B_OBJS = $(B_SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	make OBJS="$(B_OBJS)" all

.PHONY: ann clean fclean re bonus