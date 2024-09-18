# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marta <marta@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 13:36:09 by mvigara-          #+#    #+#              #
#    Updated: 2024/09/14 12:04:19 by marta            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CREATE = ar rcs
RM = rm -f
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
LPATH = -I./inc
GREEN = \033[0;32m
DEFCOLOR = \033[38;2;62;95;138m
RED = \033[38;2;150;52;54m
BLUE = \033[38;2;105;203;201m
PINK = \033[38;2;255;105;180m
YELLOW = \033[33m
RESET = \033[0m

SRC_DIR = src
OBJ_DIR = obj

SRC =	ft_memset.c ft_bzero.c ft_strlen.c ft_atoi.c ft_isdigit.c ft_isalpha.c\
ft_isprint.c ft_isascii.c ft_isalnum.c ft_memchr.c ft_memcpy.c ft_memcpy.c\
ft_memcmp.c ft_memmove.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
ft_strncmp.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_strrchr.c ft_calloc.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_substr.c\
ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_itoa.c ft_split.c ft_striteri.c\
ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_putunbr_fd.c\
ft_strndup.c ft_strnchr.c ft_printf_char.c ft_printf_nb.c ft_printf_utils.c \
ft_printf.c get_next_line.c ft_iswhitespace.c ft_atoll.c ft_strcmp.c\
ft_strtok.c ft_isodd.c ft_abs.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
INCLUDE = inc/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@$(CREATE) $(NAME) $(OBJ)
	@echo "\n${YELLOW}"
	@echo "       *       "
	@echo "      ***      "
	@echo "     *****     "
	@echo "    *******    "
	@echo "   *********   "
	@echo "  ***********  "
	@echo " ************* "
	@echo "*****${RED}libft${YELLOW}*****"
	@echo " ************* "
	@echo "  ***********  "
	@echo "   *********   "
	@echo "    *******    "
	@echo "     *****     "
	@echo "      ***      "
	@echo "       *       "
	@echo "${RESET}"
	@echo "${GREEN}libft compiled!${RESET}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(LPATH) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "${RED}libft objects removed${RESET}"

fclean: 
	@$(RM) $(NAME)
	@echo "${BLUE}libft cleaned${RESET}"

re: fclean all

.PHONY: all clean fclean re