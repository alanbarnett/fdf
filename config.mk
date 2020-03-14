# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 17:08:32 by alan              #+#    #+#              #
#    Updated: 2020/03/08 05:38:44 by alan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project
NAME :=			fdf
SRCS_DIR :=		srcs
LIBS_DIR :=		libs
INCLUDE_DIRS +=	-Iincludes

# Minilibx
LIBMLX_NAME :=	mlx
LIBMLX_DIR :=	$(LIBS_DIR)/minilibx_linux
LIBMLX :=		$(LIBMLX_DIR)/lib$(LIBMLX_NAME).a
LDFLAGS +=		-L$(LIBMLX_DIR) -l$(LIBMLX_NAME) -lXext -lX11
INCLUDE_DIRS +=	-I$(LIBMLX_DIR)
MAKE_LIBMLX :=	$(MAKE) -C $(LIBMLX_DIR) --no-print-directory

# Libft
LIBFT_NAME :=	ft
LIBFT_DIR :=	$(LIBS_DIR)/libft
LIBFT :=		$(LIBFT_DIR)/lib$(LIBFT_NAME).a
LDFLAGS +=		-L$(LIBFT_DIR) -l$(LIBFT_NAME)
INCLUDE_DIRS +=	-I$(LIBFT_DIR)/includes
MAKE_LIBFT :=	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

# Compiling
CC :=			gcc
CFLAGS +=		-Wall -Wextra -Werror $(INCLUDE_DIRS)
LDFLAGS +=		-lm -lbsd
