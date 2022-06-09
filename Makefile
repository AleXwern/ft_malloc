# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexwern <alexwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 13:14:55 by AleXwern          #+#    #+#              #
#    Updated: 2022/06/09 13:42:45 by alexwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE	= $(shell uname -m)_$(shell uname -s)
endif

NAME			= libft_malloc_$(HOSTTYPE).so
INCLUDES		= -I ./include/ -I ../libft_ASM/
LIBFT			= ../libft_ASM/libft_asm.a
FLAG			= -no-pie -fPIC -Wall -Wextra -Werror
SRC				= block_manip.c block_search.c block.c calloc.c debug.c free.c \
					heap.c hexdump.c init.c malloc.c mmap.c realloc.c
OBJ				= $(addprefix ./obj/,$(SRC:.c=.o))
GREEN			= \033[0;32m
PURPLE			= \033[0;35m
STOP			= \033[0m

.PHONY:
	clean fclean all re test

all: $(NAME)

./obj/%.o:./src/%.c
	@echo "Compiling C source $(GREEN)$@$(STOP)"
	@mkdir -p obj
	@gcc -no-pie -fPIC -g $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@echo "Building $(PURPLE)$@$(STOP)"
	@gcc $(FLAG) -shared -o $(NAME) $(INCLUDES) $(OBJ) $(LIBFT)
	@ln -sf $(NAME) libft_malloc.so

demo:
	@gcc -no-pie -fPIC -o demo $(INCLUDES) test/main.c libft_malloc.so $(LIBFTASM)

clean:
	@echo "Removing sources."
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj
	@make -C ../libft_ASM clean

fclean: clean
	@echo "Removing libraries."
	@/bin/rm -f $(NAME)
	@/bin/rm -f demo
	@/bin/rm -f libft_malloc.so
	@make -C ../libft_ASM fclean

re: fclean all
