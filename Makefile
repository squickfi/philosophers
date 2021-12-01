NAME = philo

CC = gcc

FLAGS = -pthread
#-Wall -Wextra -Werror 

MAIN_SRCS = philosophers.c\

HEADERS = philosophers.h

SRCS = $(MAIN_SRCS)
# SRCS = $(addprefix srcs/, $(MAIN_SRC))

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