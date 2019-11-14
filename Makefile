# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrias <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/11 15:15:02 by mfrias            #+#    #+#              #
#    Updated: 2019/09/30 13:45:24 by mfrias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
NAME_A	= minishell.a

CFLAG	= -Wall -Wextra -Werror
HEADER	= -I includes

SRC		= $(wildcard srcs/*.c)
OBJ		= $(patsubst %.c, %.o, $(SRC))

SUBDIR	= libft/
ARCHIVE	= libft.a

all: $(NAME) 

$(NAME): $(NAME_A)
	gcc $(CFLAG) $(SRC) $(HEADER) $(NAME_A) -o $(NAME)
	echo "COMPILED EXE"

$(NAME_A): $(OBJ)
	make -C $(SUBDIR)
	cp $(SUBDIR)$(ARCHIVE) .
	mv $(ARCHIVE) $(NAME_A)
	ar rc $(NAME_A) $(OBJ)
	ranlib $(NAME_A)
	echo "COMPILED ARCHIVE"

$(OBJ): srcs/%.o : srcs/%.c
	gcc $(CFLAG) $(HEADER) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make -C $(SUBDIR) clean
	echo "CLEANED"

fclean: clean
	rm -f $(NAME_A)
	rm -f $(NAME)
	rm -f filler.trace
	make -C $(SUBDIR) fclean
	echo "FULL CLEANED"

re: fclean all

.SILENT: clean fclean $(NAME) $(NAME_A) $(OBJ)

.PHONY: clean fclean re all 
