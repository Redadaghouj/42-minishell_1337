CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

LIB_RL := -L/goinfre/mdaghouj/homebrew/opt/readline/lib -lreadline
INCLUDE_RL := -I/goinfre/mdaghouj/homebrew/opt/readline/include

# LIB_RL := -lreadline

RM := rm -f
NAME := minishell
MANDO := mandatory
MANDO_INC := ${MANDO}/include

UTILS_PATH := ${MANDO}/src/utils
LEXER_PATH := ${MANDO}/src/parsing/lexer
PARSER_PATH := ${MANDO}/src/parsing/parser
EXPANSION_PATH := ${MANDO}/src/parsing/expansion
ENV_PATH := ${MANDO}/src/parsing/env
HEREDOC_PATH := ${MANDO}/src/parsing/heredoc
EXECUTION_PATH := ${MANDO}/src/execution

UTILS := ${UTILS_PATH}/ft_strcmp.c \
		 ${UTILS_PATH}/ft_strdup.c \
		 ${UTILS_PATH}/ft_strlen.c \
		 ${UTILS_PATH}/ft_substr.c \
		 ${UTILS_PATH}/ft_strjoin.c \
		 ${UTILS_PATH}/ft_isalpha.c \
		 ${UTILS_PATH}/ft_isdigit.c \
		 ${UTILS_PATH}/ft_isalnum.c \
		 ${UTILS_PATH}/ft_split.c \
		 ${UTILS_PATH}/ft_strchr.c \
		 ${UTILS_PATH}/ft_putstr_fd.c \
		 ${UTILS_PATH}/ft_gnl.c

LEXER := ${LEXER_PATH}/tokenize_input.c \
		 ${LEXER_PATH}/tokenize_lists.c \
		 ${LEXER_PATH}/check_operator.c

PARSER := ${PARSER_PATH}/parser.c \
		  ${PARSER_PATH}/parser_lists.c \
		  ${PARSER_PATH}/redir_lists.c \
		  ${PARSER_PATH}/check_syntax.c

EXPANSION := ${EXPANSION_PATH}/expansion.c \
		  ${EXPANSION_PATH}/expansion_utils.c \
		  ${EXPANSION_PATH}/append_args.c \
		  ${EXPANSION_PATH}/quote_cleaner.c \

ENV := ${ENV_PATH}/env.c \
	   ${ENV_PATH}/env_lists.c

HEREDOC := ${HEREDOC_PATH}/heredoc.c \
		   ${HEREDOC_PATH}/heredoc_signals.c

EXECUTION := ${EXECUTION_PATH}/execution.c \
		   ${EXECUTION_PATH}/execution_utils.c

SRC := 	${UTILS} \
		${LEXER} \
		${PARSER} \
		${EXPANSION} \
		${ENV} \
		${HEREDOC} \
		${EXECUTION} \
		${MANDO}/src/minishell.c \
		${MANDO}/src/minishell_utils.c

OBJS := ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${MANDO_INC}/minishell.h
	${CC} ${CFLAGS} ${OBJS} ${LIB_RL} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDE_RL} -c $< -o $@
# ${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re