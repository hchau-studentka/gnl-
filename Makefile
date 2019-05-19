FILES = ./libft/libft.a -I get_next_line.h main.c get_next_line.c

FLAGS = -Wall -Werror -Wextra

all:
		gcc -g $(FLAGS) $(FILES)
		./a.out

clean:
		/bin/rm -Rf a.out

re:	clean all
