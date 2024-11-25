
SRCS	= main.c

SRCS	+= utils2.c init.c utils.c launcher.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

GCC	= gcc

FLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -g 

INCLUDE	= -lpthread

HEADER	= philo.h




all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)
