# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 17:06:44 by alan              #+#    #+#              #
#    Updated: 2019/12/08 17:08:26 by alan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configuration is done in config.mk, you shouldn't need to edit this file!

# Includes all needed variables
include config.mk

C_SRCS :=		$(wildcard $(SRC_DIR)/*.c)
C_OBJS :=		$(patsubst %.c,%.o,$(C_SRCS))
C_DEPS :=		$(patsubst %.c,%.d,$(C_SRCS))
DEPFLAGS +=		-MMD -MT $@

MAKE_LIBRARY :=	make -C $(LIB_DIR) -f $(LIB_MAKEFILE) --no-print-directory
LIB :=			$(LIB_DIR)/$(LIB_NAME)

.PHONY:			all debug clean fclean re install

all: tags $(NAME)

tags: $(C_SRCS) $(LIB_SRCS)
	@- ctags -R

debug: CFLAGS += -DDEBUG_PRINT_ON -g
debug: all

$(LIB): $(LIB_SRCS)
	@ $(MAKE_LIBRARY)

$(NAME): $(LIB) $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(C_DEPS)

clean:
	@- $(RM) $(C_OBJS) $(C_DEPS)

lclean:
	@- $(MAKE_LIBRARY) clean

fclean: clean
	@- $(RM) $(NAME)

lfclean:
	@- $(MAKE_LIBRARY) fclean

re: fclean all

install: $(NAME)
	ln -siv $(shell pwd)/$(NAME) ~/bin/$(NAME)
