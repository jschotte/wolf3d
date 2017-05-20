# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschotte <jschotte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/07 17:32:23 by jschotte          #+#    #+#              #
#    Updated: 2017/05/18 08:08:09 by jschotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            =   wolf3d

SRC             =   main.c \
					draw.c \
					key.c

INC             =   ./includes/wolf.h
OBJ             =   $(addprefix $(OBJ_PATH),$(SRC:.c=.o))
CC              =   gcc
FLAGS           =   # -Wall -Wextra -Werror
FLAGS			=	#-fsanitize=thread
SRC_PATH        =   ./src/
INC_PATH        =   ./includes/
OBJ_PATH        =   ./obj/
LIB				=	libft/libft.a
SDL				=	`sdl-config --cflags --libs` 
SDLI			=   `pkg-config sdl --cflags-only-I`

all: $(NAME)

$(NAME): obj $(OBJ)
	@make -C libft/
	@$(CC) $(SDL) $(LIB) $(FLAGS) -o $(NAME)  $(OBJ)
	@printf "\n"
obj:
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@$(CC) $(FLAGS) -I $(INC_PATH) $(SDLI) -o $@ -c $<
	@printf "✅ "

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)

fclean:	clean
	@make -C libft/ fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY:	all re clean fclean
