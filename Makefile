# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 14:08:10 by cadenegr          #+#    #+#              #
#    Updated: 2025/09/30 15:18:18 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft

SRC_FILES = $(wildcard $(SRCDIR)/*.c)
#SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFTDIR)/libft_printf.a
INCLUDES = -I./include -I$(LIBFTDIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFTDIR) -lft_printf
RM = rm -rf

.PHONY: all clean fclean re test

all: $(NAME)

test: $(NAME)
	@echo "🧪 Running Pipex Test Suite..."
	@./test_pipex.sh

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all