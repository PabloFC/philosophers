NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = main.c init.c simulation.c routine.c monitor.c utils.c cleanup.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

