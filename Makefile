NAME = minishell

SRCS	= src/main.c \
		  src/signals.c \
		  src/lexer/lexer.c \
		  src/lexer/tokens.c \
		  src/parser/parser.c \
		  src/parser/ast.c \
      	  src/exec/exec_pipeline.c

OBJS = $(SRCS:.c=.o)
INCS = -I include

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

