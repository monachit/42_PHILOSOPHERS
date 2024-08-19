NAME = philo

CC = cc

CFLAGS = -Wall -g3 -fsanitize=address
SRCS = philo.c linkedlist.c utils_philo.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lpthread

clean:
	rm -f $(OBJS) 
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean