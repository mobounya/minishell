NAME = minishell

objs = main.o ft_tokenize.o ft_tokenize_helpers.o ft_builtins.o ft_env_funcs.o ft_errors.o ft_memory.o ft_split_arguments.o ft_exec_bin.o

flags = -Wall -Werror -Wextra

libft = libft/libft.a

all : $(NAME)

$(NAME) : $(objs)
	make -C libft/
	gcc $(flags) $(objs) $(libft) -o $(NAME)

%.o : %.c ./headers/minishell.h
	gcc -Wall -Werror -Wextra -c $< -o $@ 

clean :
	rm -f $(objs)
	make clean -C libft/

fclean : clean
	rm -f $(NAME)
	make fclean -C libft/

re : fclean
	make