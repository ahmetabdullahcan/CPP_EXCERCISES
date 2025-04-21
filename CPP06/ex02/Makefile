SRCS = Base.cpp A.cpp B.cpp C.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = Base

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
