NAME = philo
# NAME_BONUS =

CFLAGS = -Wall -Wextra -Werror 

SRCS = main.c libft/linked_list.c libft/fonctions.c
# SRCS_BONUS =

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

HEADER = philosopher.h

all: $(NAME)

# bonus: $(NAME_BONUS)

CC = cc

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

# $(NAME_BONUS) : $(OBJS_BONUS)
# 	$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re:  fclean all 