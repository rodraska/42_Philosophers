NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g3 #-fsanitize=address -g3 

RM = rm -f

SRCS = philosophy.c \
		utils.c \
		time.c \
		actions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME) $(OBJS)

re: fclean $(NAME)

.PHONY: all clean fclean re