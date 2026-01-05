NAME = minishell

SRCS	= src/shell/main.c \
     	  src/shell/line_exec.c \
		  src/shell/line_utils.c \
		  src/signals/signal_modes.c \
		  src/signals/signals_heredoc.c \
		  src/lexer/lexer_lex.c \
		  src/lexer/lexer_op.c \
		  src/lexer/lexer_tokens.c \
		  src/lexer/lexer_utils.c \
		  src/lexer/lexer_word.c \
		  src/parser/parser_args.c \
		  src/parser/parser_cmd.c \
		  src/parser/parser_main.c \
		  src/parser/ast.c \
		  src/exec/exec_builtin.c \
      	  src/exec/exec_pipeline.c \
		  src/exec/exec_spawn.c \
		  src/exec/exec_pipeline_spawn.c \
		  src/exec/exec_pipeline_utils.c \
		  src/exec/exec_child.c \
		  src/exec/exec_path.c \
		  src/exec/exec_redir.c \
		  src/exec/exec_utils.c \
		  src/builtins/builtin_cd.c \
		  src/builtins/builtin_echo.c \
		  src/builtins/builtin_export.c \
		  src/builtins/builtin_env.c \
		  src/builtins/builtins_utils.c \
		  src/env/env_unset.c \
		  src/env/env_utils.c \
		  src/env/env_env.c \
		  src/env/env_get.c \
		  src/builtins/builtin_exit.c \
		  src/builtins/builtin_pwd.c \
		  src/expand/expand_utils.c \
		  src/expand/expand_word.c \
		  src/expand/expand_word_utils.c \
		  src/expand/expand_cmd.c \
		  src/heredoc/hd_name.c \
		  src/heredoc/hd_write.c \
		  src/heredoc/hd_loop.c \
		  src/heredoc/hd_process.c \
		  src/heredoc/hd_setup.c \
		  src/heredoc/heredoc_utils.c \
		  src/terminal/termios.c


OBJS = $(SRCS:.c=.o)
INCS = -I include -I libft -I/opt/homebrew/opt/readline/include

COMP = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/libft.a

all: ${NAME}

.c.o: 
	${COMP} ${CFLAGS} ${INCS} -c $< -o $@

${NAME}: ${OBJS} ${LIBFT}
	${COMP} ${CFLAGS} ${OBJS} ${LIBFT} -L/opt/homebrew/opt/readline/lib -lreadline -o ${NAME}

${LIBFT}:
	@${MAKE} -C ./libft --no-print-directory

clean: 
	@rm -rf ${OBJS}
	@${MAKE} -C ./libft --no-print-directory clean

fclean: clean
	@rm -rf ${NAME}
	@${MAKE} -C ./libft --no-print-directory fclean

re: fclean all

.PHONY: all clean fclean re

