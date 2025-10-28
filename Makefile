
NAME_SERVER = server
NAME_CLIENT = client

CFFLAGS = -Wall -Wextra -Werror

SRC_SERVER = server.c
SRC_CLIENT = client.c

LIBS = libft/libft.a ft_printf/libftprintf.a

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(SRC_SERVER) $(LIBS)
	cc $(CFFLAGS) $(SRC_SERVER) $(LIBS) -o $(NAME_SERVER)

$(NAME_CLIENT): $(SRC_CLIENT) $(LIBS)
	cc $(CFFLAGS) $(SRC_CLIENT) $(LIBS) -o $(NAME_CLIENT)

$(LIBS):
	make -C libft
	make -C ft_printf

clean:
	make clean -C libft
	make clean -C ft_printf

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re