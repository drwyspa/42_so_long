# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 17:40:45 by pjedrycz          #+#    #+#              #
#    Updated: 2024/09/16 18:33:50 by pjedrycz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

SRCS		= src/so_long.c \
		  	src/map_validation.c \
		  	src/path_validation.c \
			src/path_validation_utils.c \
		  	src/movement_handling.c \
		  	src/elements_drawing.c \
		  	src/ft_split.c \
		  	src/utils.c \
			src/utils2.c

OBJS_DIR	= obj
OBJS		= $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -I includes/
LDFLAGS		= -Lmlx -lmlx -L/usr/lib/x11 -lXext -lX11

$(OBJS_DIR)/%.o: src/%.c
	@echo "Compilation im progress $<..."
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME):	$(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -g -o $(NAME)
	@echo "Compilation of $(NAME) is completed."

all:		mlx $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "Clean of $(NAME) is completed."

fclean:
	@rm -f $(NAME)
	@echo "Full clean of $(NAME) is completed."

re:			fclean all
	@echo "Rebuild of $(NAME) is completed."

mlx:
	@if [ ! -d "mlx" ] || [ -z "`ls -A mlx 2>/dev/null`" ]; then \
		echo "Cloning MinilibX repository..."; \
		rm -f mlx; \
		git clone https://github.com/42Paris/minilibx-linux.git mlx; \
		cd mlx && ./configure > /dev/null 2>&1; \
		echo "MinilibX cloned and configured."; \
	else \
		echo "MinilibX directory already exists and is not empty."; \
	fi

.PHONY:		all clean fclean re mlx