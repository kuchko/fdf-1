# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/12 20:28:36 by vrudyka           #+#    #+#              #
#    Updated: 2018/12/12 20:28:37 by vrudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=				fdf

SRC_DIR :=			./src/
OBJ_DIR :=			./obj/
INC_DIR :=			./inc/

SRC :=				main.c\
					parsing_fdf.c\
					line_draw.c\
					controls.c\
					transform.c\
					additional.c\
					colors.c
OBJ =				$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT =				$(LIBFT_DIR)libft.a
LIBFT_DIR :=		$(LIB_DIR)libft/
LIBFT_INC :=		$(LIBFT_DIR)includes/
LIBFT_FLAGS :=		-lft -L $(LIBFT_DIR)

MLX_INC :=			/usr/local/include
MLX_FLAGS :=		-L /usr/local/lib/ -lmlx

FRAMEWORKS :=		-framework OpenGL -framework AppKit

CC_FLAGS :=			-Wall -Wextra -Werror
LINK_FLAGS :=		$(MLX_FLAGS) $(LIBFT_FLAGS)
HEADER_FLAGS :=		-I $(INC_DIR)  -I $(LIBFT_INC) -I $(MLX_INC)

CC :=				gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
		gcc $(OBJ) $(LINK_FLAGS) $(FRAMEWORKS) -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
		$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
		rm -f $(OBJ)
		make clean -C $(LIBFT_DIR)

fclean: clean
		rm -f $(NAME)
		rm -rf $(OBJ_DIR)
		make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SRC_DIR)
