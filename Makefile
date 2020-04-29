# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 17:06:44 by alan              #+#    #+#              #
#    Updated: 2020/04/29 11:42:02 by abarnett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configuration is done in config.mk, you shouldn't need to edit this file!

# Includes all needed variables
include config.mk

C_SRCS :=		$(wildcard $(SRCS_DIR)/*.c)
C_OBJS :=		$(patsubst %.c,%.o,$(C_SRCS))
C_DEPS :=		$(patsubst %.c,%.d,$(C_SRCS))

.PHONY:			all debug clean lclean fclean lfclean re install

all: tags $(NAME)

tags: $(C_SRCS)
	@- ctags -R

debug: CFLAGS += -DDEBUG_PRINT_ON -g
debug: re

$(LIBMLX): $(shell find $(LIBMLX_DIR) -name "*.c")
	@ $(MAKE_LIBMLX)

$(LIBFT): $(shell find $(LIBFT_DIR) -name "*.c")
	@ $(MAKE_LIBFT)

$(NAME): $(LIBMLX) $(LIBFT) $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MT $@ -c $< -o $@

-include $(C_DEPS)

clean:
	@- $(RM) $(C_OBJS) $(C_DEPS) tags

lclean:
	@- $(MAKE_LIBMLX) clean
	@- $(MAKE_LIBFT) clean

fclean: clean
	@- $(RM) $(NAME)

lfclean:
	@- $(MAKE_LIBMLX) clean
	@- $(MAKE_LIBFT) fclean

re: fclean all

install: $(NAME)
	ln -siv $(shell pwd)/$(NAME) ~/bin/$(NAME)
