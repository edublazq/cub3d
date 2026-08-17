NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -rf

SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = include/libft
MLX42_DIR   = include/MLX42
MLX42_BUILD = build/mlx42

LIBFT       = $(LIBFT_DIR)/libft.a
MLX42_LIB   = $(MLX42_BUILD)/libmlx42.a
GLFW_LIB    = $(shell pkg-config --libs glfw3)

INCLUDES    = -I include -I $(MLX42_DIR)/include

LDFLAGS     = -L $(LIBFT_DIR) -lft \
              -L $(MLX42_BUILD) -lmlx42 \
              $(GLFW_LIB) \
              -ldl -pthread -lm

HEADERS     = include/cub3d.h include/render.h

SRCS        = src/main.c src/render/mlx_init.c src/render/vec2.c \
			  src/check.c src/gnl.c src/file_checkers.c \
			  src/map_checkers.c src/utils.c src/data.c \

OBJS        = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

mlx: $(MLX42_LIB)

$(MLX42_LIB):
	cmake -B $(MLX42_BUILD) $(MLX42_DIR) --log-level=WARNING
	cmake --build $(MLX42_BUILD) -j$(shell nproc)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean_mlx: fclean
	$(RM) $(MLX42_BUILD)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all mlx clean fclean fclean_mlx re