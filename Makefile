NAME = philo
NAME_BONUS = philo_b

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

SRCS = main.c src/linked_list.c src/fonctions.c src/rotine.c src/fonctions2.c
SRCS_FOLDER = philo
SRCS_BONUS = main.c src/linked_list.c src/fonctions.c src/rotine.c src/fonctions2.c
SRCS_BNS_FOLDER = philo_bonus

OBJS = $(SRCS:$(SRCS_FOLDER)/.c=.o)

OBJS_BONUS = $(SRCS_BONUS:$(SRCS_BNS_FOLDER)/.c=.o)

HEADER = philosopher.h

all: $(NAME)

bonus: $(NAME_BONUS)

CC = cc

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS_FOLDER)/$(OBJS) -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS)
	$(CC) $(SRCS_BNS_FOLDER)/$(OBJS_BONUS) -o $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re:  fclean all 