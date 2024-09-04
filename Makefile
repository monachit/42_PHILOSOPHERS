NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c linkedlist.c utils_philo.c	help.c help2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
	rm -f $(OBJS) 
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
