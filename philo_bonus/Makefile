NAME_BONUS = philo_b

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

SRCS_BONUS = main.c src/linked_list.c src/fonctions.c src/rotine.c src/fonctions2.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

HEADER = philosopher.h

all: $(NAME_BONUS)

bonus: $(NAME_BONUS)

CC = cc

$(NAME_BONUS) : $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf  $(OBJS_BONUS)

fclean: clean
	rm -rf  $(NAME_BONUS)

re:  fclean all 