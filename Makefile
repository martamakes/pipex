# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marta <marta@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 15:55:17 by mvigara           #+#    #+#              #
#    Updated: 2024/09/14 12:01:53 by marta            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
LIBFT_DIR = lib/libft

# SRC and OBJ files
SRC_FILES = pipex.c utils.c
BONUS_FILES = pipex_bonus.c here_doc_bonus.c cmd_execution_bonus.c process_utils_bonus.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
BONUS_SRCS = $(addprefix $(SRC_DIR)/, $(BONUS_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Pipex compiled!$(RESET)"
	@$(MAKE) display_art

$(NAME_BONUS): $(LIBFT) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -o $(NAME_BONUS)
	@echo "$(GREEN)Pipex bonus compiled!$(RESET)"
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
	@$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)Pipex cleaned$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re display_art

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