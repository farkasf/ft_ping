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

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;36m
YELLOW = \033[1;33m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)compiling libft$(NC)"
	@make all -C ./libft
	@echo "$(BLUE)linking object files$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(RED)$(NAME) ready$(NC)"

%.o: %.c
	@echo "$(BLUE)compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	@echo "$(YELLOW)clean done.$(NC)"
	@$(R) $(OBJS)
	@${MAKE} clean -C ./libft

fclean: clean
	@echo "$(GREEN)full clean done.$(NC)"
	@$(R) $(NAME)
	@${MAKE} fclean -C ./libft

re: fclean all
