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
BLUE = \033[0;34m
YELLOW = \033[1;33m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling libft..."
	@make all -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) ready$(NC)"

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	@echo "$(YELLOW)Cleaning...$(NC)"
	@$(R) $(OBJS)
	@${MAKE} clean -C ./libft

fclean: clean
	@echo "$(RED)Full clean done.$(NC)"
	@$(R) $(NAME)
	@${MAKE} fclean -C ./libft

re: fclean all
