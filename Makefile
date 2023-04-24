### Compilation ###
CC      = cc
# FLAGS  = -Wall -Wextra -Werror -g
FLAGS  = -g
### Executable ###
NAME   = cub3D
### Includes ###
OBJ_PATH  = objs/
HEADER = includes/
SRC_PATH  = sources/
LIBFT = libft/

### Source Files ###
COR_DIR		=	core/
CORS		=	main.c

PARSE_DIR	=	[0]parsing/
PARSE		=	[0]read_map.c [1]parsing_map.c

# EXEC_DIR	=	exec/
# EXEC		=	exec_core.c fill_heredocs.c path.c cmd_signals.c main_hrdc_signals.c \
# 				exec_builtins.c error_msgs.c fill_file_index.c fill_file_index_utils.c \
# 				define_dups.c define_dups_utils.c exec_core2.c\
# 				exec_controls.c executions.c executions_utils.c init_magic.c

# BUILTIN_DIR	=	builtin/
# BUILTIN		=	echo.c export.c export_utils.c unset.c cd.c cd_path_case.c export_unset_utils.c \
# 				pwd.c exit.c

# UTILS_DIR	=	utils/
# UTILS		=	env_list.c env_list_2.c env_list_3.c generic_list.c generic_list_2.c \
# 				token_list.c token_list_2.c hrdoc_list.c hrdoc_list_utils.c \
# 				comand_list.c comand_list_utils.c general_utils.c 

SOURCES		+=	$(addprefix	$(COR_DIR),$(CORS))
# SOURCES		+=	$(addprefix	$(EXEC_DIR),$(EXEC))
SOURCES		+=	$(addprefix	$(PARSE_DIR),$(PARSE))
# SOURCES		+=	$(addprefix	$(BUILTIN_DIR),$(BUILTIN))
# SOURCES		+=	$(addprefix	$(UTILS_DIR),$(UTILS))

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
	@make --no-print-directory -C $(LIBFT)

tmp:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)$(COR_DIR)
	@mkdir -p $(OBJ_PATH)$(PARSE_DIR)
# @mkdir -p $(OBJ_PATH)$(EXEC_DIR)
# @mkdir -p $(OBJ_PATH)$(BUILTIN_DIR)
# @mkdir -p $(OBJ_PATH)$(UTILS_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -L $(LIBFT) -o $@ $^ -lm -l:libft.a
	@echo "$(GREEN)Project compiled succesfully$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) -MMD -c -o $@ $<
	@echo "$(CYAN)Creation of object file -> $(CYAN)$(notdir $@)... $(GREEN)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Cleaning libraries$(NOC)"
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "$(GREEN)Cleaning libraries files$(NOC)"
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

-include $(DEPS)

.PHONY: tmp, re, fclean, clean
