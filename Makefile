CC= cc

CFLAGS= -Wall -Wextra -Werror -pthread

HDR = philosophers.h

SRC = philosophers.c  routine.c

OBJ = $(SRC:.c=.o)

NAME = philosophers

all: philosophers

$(NAME) : $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf  $(OBJ) $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all