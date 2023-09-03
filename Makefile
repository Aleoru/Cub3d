# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 18:12:15 by aoropeza          #+#    #+#              #
#    Updated: 2023/09/03 02:33:01 by fgalan-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRCDIR	= src
OBJDIR	= obj
LIBFT	= lib/libft
LIBMLX	= lib/MLX42

HEADER	= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc
LFLAGS	= -L$(LIBFT) -lft  -L$(LIBMLX) -lmlx42 
# LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/
LIBS	= -ldl -lglfw -lm
# SRC_B	:= $(wildcard $(SRCDIR)/bonus/*.c)
SRC		:= $(wildcard $(SRCDIR)/*/*.c)
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
# OBJS_B	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_B))

CC 		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM 		= rm -rf

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

all: libmlx libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBS) $(HEADER) -o $(NAME) &&\
	printf "$(GREEN)$(BOLD)Welcome to doom beginnings\n$(RESET)"

#bonus: libmlx libft $(OBJS_B)
#	@$(CC) $(CFLAGS) $(OBJS_B) $(LFLAGS) $(LIBS) $(HEADER) -o $(NAME) &&\
	printf "$(GREEN)$(BOLD)So Long game ready to play!\n$(RESET)"

obj/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADER) && printf "$(WHITE)$(BOLD)\rCompiling: \
	$(CYAN)$(notdir $@)$(GREEN)\r\e[35C[OK]\n$(RESET)"

clean:
	@$(RM) $(OBJDIR) && printf "$(GREEN)$(BOLD)All objects cleaned! :)\n$(RESET)"
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@$(RM) $(NAME) && printf "$(YELLOW)$(BOLD)$(NAME) $(GREEN)file cleaned! :)\n$(RESET)"
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all bonus clean fclean re
