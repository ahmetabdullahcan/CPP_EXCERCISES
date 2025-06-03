NAME = PmergeMe
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98
SRC = main.cpp PmergeMe.cpp PmergeMe.hpp

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

re: clean all

clean:
	rm -f $(NAME)

fclean: clean

.PHONY: all clean re
