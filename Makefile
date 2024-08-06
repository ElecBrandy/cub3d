CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -g -Wall -Wextra -Werror
# CFLAGS = -g -fsanitize=address
NAME = cub3d
INCS = includes

# MLX
MLX_DIR = ./files/minilibx_mms_20210621/
MLX_LIB = libmlx.dylib
MLX_FLAGS = -L. -lmlx -framework OpenGL -framework AppKit -lz

SRCS_U = \

SRCS_M = \
	$(SRCS_U)

OBJS_M = $(SRCS_M:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS_M)
	$(CC) $(CFLAGS) $(OBJS_M) -o $(NAME) $(MLX_FLAGS) -I$(INCS)

$(MLX_LIB): $(MLX_DIR)$(MLX_LIB)
	cp $(MLX_DIR)$(MLX_LIB) .

$(MLX_DIR)$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCS) -o $@ -c $<

clean:
	@rm -f $(OBJS_M)

fclean: clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(NAME)
	@rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re mlx_comp