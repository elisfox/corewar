# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 19:24:15 by gdoze             #+#    #+#              #
#    Updated: 2021/01/05 13:33:06 by jojoseph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ПОЧЕМУ ПЕРЕКОМПИЛИВАЕТСЯ АСМ?????
ASM_NAME = asmo
VM_NAME = corewar

FLAGS = -Wall -Werror -Wextra

# Libraries and Includes

ASM_LIB = -lftprintf -L$(FT_PRINTF_DIR)
ASM_INCL = \
	-I$(HEADERS_DIR)\
	-I$(HEADERS_LIBFT)\
	-I$(HEADERS_FT_PRINTF)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./ft_printf/libft/
HEADERS_LIBFT = $(LIBFT_DIR)includes/

FT_PRINTF = $(FT_PRINTF_DIR)libftprintf.a
FT_PRINTF_DIR = ./ft_printf/
HEADERS_FT_PRINTF = $(FT_PRINTF_DIR)includes/

# Headers

HEADERS_DIR = ./includes/

# asm

ASM_HEADERS_LIST = \
	op.h\
	asm.h\
	asm_op.h\
    asm_error.h
ASM_HEADERS = $(addprefix $(HEADERS_DIR), $(ASM_HEADERS_LIST))

ASM_SRS_DIR = ./src/asm/

ASM_SRS_LIST = \
	main.c \
    init.c \
    geting_line.c\
    parser.c \
    parser_search.c \
    parser_helpers.c\
    work_data.c\
    translate_code.c\
    translate_code_dop.c\
    translate_args.c\
    add_args.c\
    write_to_file.c\
    free.c\
    handling_error.c\
    error_info.c\
	utils.c

# vm

VM_HEADERS_LIST = \
	op.h\
	corewar.h
VM_HEADERS = $(addprefix $(HEADERS_DIR), $(VM_HEADERS_LIST))

VM_SRS_DIR = ./src/corewar/

VM_SRS_LIST = \
	main.c \
	free_exit.c \
	init.c \
	arena.c \
	print.c \

# Objects

OBJ_DIR = ./objects/

ASM_OBJ_DIR = $(OBJ_DIR)asm/
ASM_OBJ_LIST = $(patsubst %.c, %.o, $(ASM_SRS_LIST))
ASM_OBJ	= $(addprefix $(ASM_OBJ_DIR), $(ASM_OBJ_LIST))

VM_OBJ_DIR = $(OBJ_DIR)corewar/
VM_OBJ_LIST = $(patsubst %.c, %.o, $(VM_SRS_LIST))
VM_OBJ	= $(addprefix $(VM_OBJ_DIR), $(VM_OBJ_LIST))

# COLORS

CYAN = \033[1;36m
YELLOW = \033[1;33m
RESET = \033[0m

.PHONY: all clean fclean re

all:$(ASM_NAME) $(VM_NAME)

$(ASM_NAME): $(FT_PRINTF) $(ASM_OBJ_DIR)  $(ASM_OBJ)
	@$gcc $(FLAGS) $(ASM_LIB) $(ASM_INCL) $(ASM_OBJ)  -o $(ASM_NAME)
	@echo "\n$(CYAN)✓️ object files were created$(RESET)"
	@echo "$(CYAN)✓️ asm was created$(RESET)"
	@mv asmo asm

$(ASM_OBJ_DIR):
	@mkdir -p $(ASM_OBJ_DIR)

$(ASM_OBJ_DIR)%.o : $(ASM_SRS_DIR)%.c $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(ASM_INCL) $< -o $@
	@echo "$(CYAN)▆$(RESET)\c"
	

$(VM_NAME): $(FT_PRINTF) $(VM_OBJ_DIR)  $(VM_OBJ)
	@$gcc $(FLAGS) $(ASM_LIB) $(ASM_INCL) $(VM_OBJ)  -o $(VM_NAME)
	@echo "\n$(CYAN)✓️ object files were created$(RESET)"
	@echo "$(CYAN)✓️ corewar was created$(RESET)"

$(VM_OBJ_DIR):
	@mkdir -p $(VM_OBJ_DIR)

$(VM_OBJ_DIR)%.o : $(VM_SRS_DIR)%.c $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(ASM_INCL) $< -o $@
	@echo "$(CYAN)▆$(RESET)\c"

$(FT_PRINTF):
	@echo "$(CYAN)Creating project...$(RESET)"
	@$(MAKE) -sC $(FT_PRINTF_DIR)
	@echo "$(CYAN)✓  libftprintf.a was created$(RESET)"

clean:
	@$(MAKE) -sC $(FT_PRINTF_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)✓️ object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -sC $(FT_PRINTF_DIR) fclean
	@echo "$(YELLOW)✓ libftprintf.a was deleted$(RESET)"
	@rm -f $(ASM_NAME) asm
	@echo "$(YELLOW)✓️ asm was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
