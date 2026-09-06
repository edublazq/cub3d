NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -o2
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
			  src/render/draw_minimap.c src/render/draw_3d.c \
			  src/render/move.c src/render/rotate.c \
			  src/check.c src/gnl.c src/file_checkers.c \
			  src/map_checkers.c src/utils.c \
			  src/data/get_data_for_map.c src/data/map_grid.c \
			  src/data/map_header.c src/data/get_data_for_player.c \
			  src/render/raycasting/aux.c src/render/raycasting/raycast.c \

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

fclean: clean fclean_mlx
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean_mlx: fclean
	$(RM) $(MLX42_BUILD)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all mlx clean fclean fclean_mlx re