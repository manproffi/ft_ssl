# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sprotsen <sprotsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/21 12:02:20 by sprotsen          #+#    #+#              #
#    Updated: 2017/05/21 12:02:22 by sprotsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

LIB_NAME = ft

#LIB_NAME2 = ftprintf

LIB_DIR = ./lib_folder/libft

#LIB_DIR2 = ./lib_folder/ft_printf

LIB_ALL = -L$(LIB_DIR) -l$(LIB_NAME) #-L$(LIB_DIR2) -l$(LIB_NAME2)

SRC = main.c parsing_command.c \
    md5_algo.c append_padding_bits.c fun.c fun_round.c read_screen.c read_file.c \
    print_result.c  pre_parsing_flags.c control_s_flags.c fill_content.c \
    choice_algorithm_function.c sha256_algo.c append_padding_bits_256.c
 
OBJ = $(SRC:.c=.o)

#FLAG = -Wall -Wextra -Werror

all:	$(NAME)

$(NAME): lib $(OBJ) head_ssl.h
	gcc $(FLAG) $(OBJ) -o $(NAME) $(LIB_ALL)

%.o: %.c head_ssl.h
	gcc $(FLAG) -c -o $@ $<

lib:
	make -C lib_folder/libft
	#make -C lib_folder/ft_printf

clean:
	$(MAKE) clean -C lib_folder/libft
	#$(MAKE) clean -C lib_folder/ft_printf
	rm -f $(OBJ)

fclean:	clean
	$(MAKE) fclean -C lib_folder/libft
	#$(MAKE) fclean -C lib_folder/ft_printf
	rm -f $(NAME)

re: fclean lib all	