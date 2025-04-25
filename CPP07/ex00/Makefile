SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = Templates

COMPAILER = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -f

all: $(NAME)
$(NAME): $(OBJS)
	$(COMPAILER) $(CFLAGS) -o $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
