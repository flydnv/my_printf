CC = gcc
CFLAGS = -Wall -Wextra -Werror
SANFLAGS = -g3 -fsanitize=address
SRC = my_printf.c main.c
OBJ = $(SRC:.c=.o)
NAME = test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	$(CC) $(CFLAGS) $(SANFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re