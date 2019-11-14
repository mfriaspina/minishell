# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrias <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/29 17:06:24 by mfrias            #+#    #+#              #
#    Updated: 2019/04/29 17:32:46 by mfrias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc $(CFLAG) -c *.c
	ar rc $(NAME) *.o

clean:	
	rm -f *.o*

fclean: clean
	rm -f $(NAME)

re: fclean all

