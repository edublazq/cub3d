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
GLFW_LIB    = $(MLX42_BUILD)/_deps/glfw-build/src/libglfw3.a

INCLUDES    = -I include -I $(MLX42_DIR)/include

LDFLAGS     = -L $(LIBFT_DIR) -lft \
              -L $(MLX42_BUILD) -lmlx42 \
              $(GLFW_LIB) \
              -ldl -pthread -lm

SRCS        = src/main.c \
              src/parse.c

OBJS        = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_LIB):
	cmake -B $(MLX42_BUILD) $(MLX42_DIR) --log-level=WARNING
	cmake --build $(MLX42_BUILD) -j$(shell nproc)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(MLX42_BUILD)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re