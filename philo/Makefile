NAME = philo

CFLAGS = -Wall -Wextra -Werror 

SRCS = main.c src/linked_list.c src/fonctions.c src/rotine.c src/fonctions2.c

OBJS = $(SRCS:.c=.o)

HEADER = philosopher.h

all: $(NAME)

CC = cc

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:  fclean all
