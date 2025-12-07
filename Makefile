NAME = minishell

SRCS	= src/main.c \
		  src/signals.c \
		  src/lexer/lexer_lex.c \
		  src/lexer/lexer_op.c \
		  src/lexer/lexer_tokens.c \
		  src/lexer/lexer_utils.c \
		  src/lexer/lexer_word.c \
		  src/parser/parser_args.c \
		  src/parser/parser_cmd.c \
		  src/parser/parser_main.c \
		  src/parser/ast.c \
      	  src/exec/exec_pipeline.c

OBJS = $(SRCS:.c=.o)
INCS = -I include -I libft

COMP = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/libft.a

all: ${NAME}

.c.o: 
	${COMP} ${CFLAGS} ${INCS} -c $< -o $@

${NAME}: ${OBJS} ${LIBFT}
	@${COMP} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

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

