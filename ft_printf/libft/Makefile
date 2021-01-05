# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdoze <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 19:24:54 by gdoze             #+#    #+#              #
#    Updated: 2020/10/31 19:24:56 by gdoze            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra -O3 -c
INCLUDES = -I$(HEADERS_DIR)
HEADERS_LIST = \
	libft.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))
SRS_DIR = ./sources/
SRS_LIST = \
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strlen.c\
	ft_strdup.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_atoi.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_memalloc.c\
	ft_memdel.c\
	ft_strnew.c\
	ft_strdel.c\
	ft_strclr.c\
	ft_striter.c\
	ft_strmap.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_strsplit.c\
	ft_itoa.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putendl.c\
	ft_putnbr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_isupper.c\
	ft_islower.c\
	ft_isspace.c\
	ft_isblank.c\
	ft_strnlen.c\
	ft_strndup.c\
	ft_strchrs.c\
	ft_strsubchr.c\
	ft_isdigit_base.c\
	ft_isprefix.c\
	ft_isnum.c\
	ft_signedlen.c\
	ft_unsignedlen.c\
	ft_pow_int.c\
	ft_atoi32.c\
	ft_ftoa_long.c\
	ft_ftoa.c\
	ft_itoa_unsigned.c\
	ft_itoa_long.c\
	ft_itoa_longlong.c\
	ft_itoa_base.c\
	ft_iszero.c\
	ft_strjoin_free.c\
	ft_swap.c
SRS = $(addprefix $(SRS_DIR), $(SRS_LIST))
OBJ_DIR = objects/
OBJ_LIST = $(patsubst %.c, %.o, $(SRS_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

CYAN = \033[1;36m
YELLOW = \033[1;33m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n$(CYAN)✓️ $(NAME) was created$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRS_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@
	@echo "$(CYAN)▆$(RESET)\c"

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)✓️ $(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
