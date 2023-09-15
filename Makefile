# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 14:12:28 by flmartin          #+#    #+#              #
#    Updated: 2023/09/15 15:54:10 by flmartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src/
BIN_DIR = bin/
INC_DIR = inc/

SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ_FILES = $(addprefix $(BIN_DIR), $(notdir $(SRC_FILES:.c=.o)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

$(BIN_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BIN_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

