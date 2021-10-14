# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 13:14:55 by AleXwern          #+#    #+#              #
#    Updated: 2021/10/14 23:31:11 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE	= $(shell uname -m)_$(shell uname -s)
endif

NAME			= libft_malloc_$(HOSTTYPE).so
INCLUDES		= -I ./include/ -I ./libft/
LIBFT			= libft/libft.a
LIBFTASM		= libft/libft_asm.a
FLAG			= -Wall -Wextra -Werror
SRC				= block_search.c block.c free.c heap.c init.c malloc.c mmap.c \
					debug.c
OBJ				= $(addprefix ./obj/,$(SRC:.c=.o))

.PHONY:
	clean fclean all re test

all: $(NAME)

./obj/%.o:./src/%.c
	@echo "Compiling C source $<"
	@mkdir -p obj
	@gcc -fPIC -g $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

$(LIBFTASM):
	@make -C libft LibftASM

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAG) -shared -o $(NAME) $(INCLUDES) $(OBJ) $(LIBFT)
	ln -sf $(NAME) libft_malloc.so

asm: $(LIBFTASM) $(OBJ)
	gcc -no-pie $(FLAG) -shared -o $(NAME) $(INCLUDES) $(OBJ) $(LIBFTASM)
	ln -sf $(NAME) libft_malloc.so

demo:
	gcc -o demo $(INCLUDES) test/main.c libft_malloc.so $(LIBFTASM)

clean:
	@echo "Removing sources."
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj
	@make -C libft clean

fclean: clean
	@echo "Removing libraries."
	@/bin/rm -f $(NAME)
	@/bin/rm -f demo
	@/bin/rm -f libft_malloc.so
	@make -C libft fclean

re: fclean all

reasm: fclean asm
