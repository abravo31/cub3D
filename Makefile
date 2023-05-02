### Compilation ###
CC      = cc
FLAGS  = -Wall -Wextra -Werror -g
### Executable ###
NAME   = cub3D
### Includes ###
OBJ_PATH  = objs/
HEADER = includes/
SRC_PATH  = sources/
INC_PATH  = includes/
LIBFT = libft/
MLX_LINUX	=	minilibx-linux/
# COMMENT FOR COMPILE
# MLX_LINUX_FLAGS	=	-L. -lXext -L. -lX11 -lm -lbsd
MLX_LINUX_FLAGS = -lm
# FLAGS += -I$(INC_PATH)
### Source Files ###
COR_DIR		=	core/
CORS		=	main.c

PARSE_DIR	=	[0]parsing/
PARSE		=	[0]arguments.c [0]read_map.c [1]parsing_identifier.c [1]parsing_identifier_coord.c [1]parsing_map.c \
				[1]parsing_identifier_fc.c [1]parsing_identifier_free.c [1]parsing_identifier_map.c [1]parsing_identifier_tools.c

# COMMENT FOR COMPILE
# EXEC_DIR	=	[1]execution/
# EXEC		=	[0]window.c [1]mlx_tools.c [2]mini_map.c

# BUILTIN_DIR	=	builtin/
# BUILTIN		=	echo.c export.c export_utils.c unset.c cd.c cd_path_case.c export_unset_utils.c \
# 				pwd.c exit.c

UTILS_DIR	=	utils/
UTILS		=	lst_new_generic.c debuging_list_of_structs.c

SOURCES		+=	$(addprefix	$(COR_DIR),$(CORS))
# COMMENT FOR COMPILE
# SOURCES		+=	$(addprefix	$(EXEC_DIR),$(EXEC))
SOURCES		+=	$(addprefix	$(PARSE_DIR),$(PARSE))
# SOURCES		+=	$(addprefix	$(BUILTIN_DIR),$(BUILTIN))
SOURCES		+=	$(addprefix	$(UTILS_DIR),$(UTILS))

### Objects ###

SRCS = $(addprefix $(SRC_PATH),$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.o))
DEPS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.d))

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

### RULES ###


all: lib tmp $(NAME)

lib:
	@make --no-print-directory -s -C $(LIBFT)
# COMMENT FOR COMPILE
# @make --no-print-directory -s -C $(MLX_LINUX)

tmp:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)$(COR_DIR)
	@mkdir -p $(OBJ_PATH)$(PARSE_DIR)
	@mkdir -p $(OBJ_PATH)$(EXEC_DIR)
# COMMENT FOR COMPILE
# @mkdir -p $(OBJ_PATH)$(BUILTIN_DIR)
	@mkdir -p $(OBJ_PATH)$(UTILS_DIR)

$(NAME): $(OBJS)
# COMMENT FOR COMPILE
# $(CC) $(FLAGS) -L $(LIBFT) -L $(MLX_LINUX) -o $@ $^ -lm -l:libft.a -l:libmlx.a $(MLX_LINUX_FLAGS)
# $(CC) $(FLAGS) -L $(LIBFT) -L $(MLX_LINUX) -o $@ $^ -lm -l:libft.a
	$(CC) $(FLAGS) -L $(LIBFT) -o $@ $^ -lm -l:libft.a
	@echo "$(GREEN)Project compiled succesfully$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) -MMD -c -o $@ $<
	@echo "$(CYAN)Creation of object file -> $(CYAN)$(notdir $@)... $(GREEN)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Cleaning libraries$(NOC)"
	@make -s clean -C $(LIBFT)
# COMMENT FOR COMPILE
# @make -s clean -C $(MLX_LINUX)
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "$(GREEN)Cleaning libraries files$(NOC)"
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@make -s fclean -C $(LIBFT)
	
# @make -s clean -C $(MLX_LINUX)

re: fclean all

-include $(DEPS)

.PHONY: tmp, re, fclean, clean
