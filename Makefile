NAME = minishell

INCLUDES = includes/
LIBFT_PATH = libft/

SRCS = srcs/main.c \
       srcs/builtins/cd.c \
       srcs/builtins/echo.c \
       srcs/builtins/env.c \
       srcs/builtins/exit.c \
       srcs/builtins/export.c \
       srcs/builtins/pwd.c \
       srcs/builtins/unset.c \
       srcs/builtins/exit_utils.c \
       srcs/execution/executor.c \
       srcs/execution/handle_cmd.c \
       srcs/execution/handle_cmd_utils.c \
       srcs/execution/handle_pipes.c \
       srcs/execution/pipe_utils.c\
       srcs/execution/check_redirections.c \
       srcs/execution/heredoc.c\
       srcs/execution/heredoc_utils.c\
       srcs/parsing/lexer.c \
       srcs/parsing/parser.c \
       srcs/parsing/parsing_utils.c \
       srcs/parsing/utils.c \
       srcs/parsing/utils2.c \
       srcs/parsing/utils_3.c \
       srcs/parsing/utils_4.c \
       srcs/parsing/expander_utils.c \
       srcs/parsing/expander_utils_2.c \
       srcs/parsing/expander_utils_3.c \
       srcs/parsing/expander.c \
       srcs/parsing/utils_1.c\
       srcs/utils/signal_handler.c \
       srcs/utils/env_utils.c\
       srcs/utils/env_utils_2.c\
       srcs/utils/pipe_fork.c\
       srcs/utils/builtins_utils.c \
       srcs/utils/free_utils.c \
       srcs/utils/handle_utils.c\
       srcs/utils/free_utils_2.c\
       srcs/utils/libft_utils.c\
       srcs/utils/libft_utils_2.c\
       srcs/utils/print_error.c\
       srcs/utils/garbage_collector.c


CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

READLINE_INC = -I/usr/include -I/usr/local/opt/readline/include
READLINE_LIB = -L/usr/lib -L/usr/local/opt/readline/lib -lreadline
READLINE_FLAGS = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include


GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(READLINE_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -I$(LIBFT_PATH) $(READLINE_FLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJS)
	@echo "$(RED)🧹 Object files removed!$(RESET)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)🧹 $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re