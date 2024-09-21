NAME = ft_ping
LIBFT = ./libft/libft.a
SRC =	./src/echo_packet.c \
		./src/error_log.c \
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
	make all -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	$(R) $(OBJS)
	${MAKE} clean -C ./libft

fclean: clean
	$(R) $(NAME)
	${MAKE} fclean -C ./libft

re: fclean all
