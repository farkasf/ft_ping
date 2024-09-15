NAME = ft_ping
SRC =	./src/echo_packet.c \
		./src/ft_ping.c \
		./src/parser.c \
		./src/ping_routine.c \
		./src/socket.c \
		./src/response.c \
		./src/utils.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
INCL = -I ./incl
R = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	$(R) $(OBJS)

fclean: clean
	$(R) $(NAME)

re: fclean all
