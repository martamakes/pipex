# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marta <marta@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 15:55:17 by mvigara           #+#    #+#              #
#    Updated: 2024/09/14 14:42:31 by marta            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
LIBFT_DIR = lib/libft

# SRC and OBJ files
SRC_FILES = pipex.c utils.c path.c path_utils.c errors.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)/inc

# Includes
INC = -I$(INC_DIR) -I$(LIBFT_INC)

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Pipex compiled!$(RESET)"
	@$(MAKE) display_art

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Pipex objects removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)Pipex cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re display_art

# Display art
define PIPEX_ART
$(RED)██████╗ $(YELLOW)██╗$(GREEN)██████╗ $(BLUE)███████╗$(PURPLE)██╗  ██╗
$(RED)██╔══██╗$(YELLOW)██║$(GREEN)██╔══██╗$(BLUE)██╔════╝$(PURPLE)╚██╗██╔╝
$(RED)██████╔╝$(YELLOW)██║$(GREEN)██████╔╝$(BLUE)█████╗  $(PURPLE) ╚███╔╝ 
$(RED)██╔═══╝ $(YELLOW)██║$(GREEN)██╔═══╝ $(BLUE)██╔══╝  $(PURPLE) ██╔██╗ 
$(RED)██║     $(YELLOW)██║$(GREEN)██║     $(BLUE)███████╗$(PURPLE)██╔╝ ██╗
$(RED)╚═╝     $(YELLOW)╚═╝$(GREEN)╚═╝     $(BLUE)╚══════╝$(PURPLE)╚═╝  ╚═╝
$(RESET)
endef
export PIPEX_ART

display_art:
	@echo "$$PIPEX_ART"