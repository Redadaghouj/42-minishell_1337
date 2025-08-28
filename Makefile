# Color Definitions
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
RESET   := \033[0m

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

LIB_RL := -L/goinfre/mdaghouj/homebrew/opt/readline/lib -lreadline
INCLUDE_RL := -I/goinfre/mdaghouj/homebrew/opt/readline/include

RM := rm -f
NAME := minishell

MANDO := mandatory
MANDO_INC := ${MANDO}/include
BONUS := bonus
BONUS_INC := ${BONUS}/include

# ============ MANDATORY SOURCES ============
UTILS_PATH := ${MANDO}/src/utils
LEXER_PATH := ${MANDO}/src/parsing/lexer
PARSER_PATH := ${MANDO}/src/parsing/parser
EXPANSION_PATH := ${MANDO}/src/parsing/expansion
ENV_PATH := ${MANDO}/src/parsing/env
HEREDOC_PATH := ${MANDO}/src/parsing/heredoc
EXECUTION_PATH := ${MANDO}/src/execution

UTILS := ${UTILS_PATH}/ft_strcmp.c \
		 ${UTILS_PATH}/ft_strncmp.c \
		 ${UTILS_PATH}/ft_strdup.c \
		 ${UTILS_PATH}/ft_strlen.c \
		 ${UTILS_PATH}/ft_substr.c \
		 ${UTILS_PATH}/ft_strjoin.c \
		 ${UTILS_PATH}/rb_strjoin.c \
		 ${UTILS_PATH}/ft_isalpha.c \
		 ${UTILS_PATH}/ft_isdigit.c \
		 ${UTILS_PATH}/ft_isalnum.c \
		 ${UTILS_PATH}/ft_split.c \
		 ${UTILS_PATH}/ft_strchr.c \
		 ${UTILS_PATH}/ft_putstr_fd.c \
		 ${UTILS_PATH}/ft_atoi.c \
		 ${UTILS_PATH}/ft_itoa.c \
         ${UTILS_PATH}/gnl/get_next_line.c \
         ${UTILS_PATH}/gnl/get_next_line_utils.c

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
		  ${EXPANSION_PATH}/quote_cleaner.c

ENV := ${ENV_PATH}/env.c \
	   ${ENV_PATH}/env_lists.c

HEREDOC := ${HEREDOC_PATH}/heredoc.c \
		   ${HEREDOC_PATH}/heredoc_signals.c

EXECUTION := ${EXECUTION_PATH}/execution.c \
		   ${EXECUTION_PATH}/execution_utils.c \
		   ${EXECUTION_PATH}/builtins/cd.c \
		   ${EXECUTION_PATH}/builtins/echo.c \
		   ${EXECUTION_PATH}/builtins/env.c \
		   ${EXECUTION_PATH}/builtins/exit.c \
		   ${EXECUTION_PATH}/builtins/export.c \
		   ${EXECUTION_PATH}/builtins/pwd.c \
		   ${EXECUTION_PATH}/builtins/unset.c \
		   ${EXECUTION_PATH}/pipe/pipe.c \
		   ${EXECUTION_PATH}/redirection/redir.c \
		   ${EXECUTION_PATH}/redirection/ambiguous_redir.c

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

# ============ BONUS SOURCES ============
BONUS_UTILS_PATH := ${BONUS}/src/utils
BONUS_LEXER_PATH := ${BONUS}/src/parsing/lexer
BONUS_PARSER_PATH := ${BONUS}/src/parsing/parser
BONUS_EXPANSION_PATH := ${BONUS}/src/parsing/expansion
BONUS_ENV_PATH := ${BONUS}/src/parsing/env
BONUS_HEREDOC_PATH := ${BONUS}/src/parsing/heredoc
BONUS_EXECUTION_PATH := ${BONUS}/src/execution

BONUS_UTILS := ${BONUS_UTILS_PATH}/ft_strcmp_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_strncmp_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_strdup_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_strlen_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_substr_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_strjoin_bonus.c \
			   ${BONUS_UTILS_PATH}/rb_strjoin_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_isalpha_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_isdigit_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_isalnum_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_split_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_strchr_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_putstr_fd_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_atoi_bonus.c \
			   ${BONUS_UTILS_PATH}/ft_itoa_bonus.c \
			   ${BONUS_UTILS_PATH}/gnl/get_next_line_bonus.c \
			   ${BONUS_UTILS_PATH}/gnl/get_next_line_utils_bonus.c

BONUS_LEXER := ${BONUS_LEXER_PATH}/tokenize_input_bonus.c \
			   ${BONUS_LEXER_PATH}/tokenize_lists_bonus.c \
			   ${BONUS_LEXER_PATH}/check_operator_bonus.c

BONUS_PARSER := ${BONUS_PARSER_PATH}/parser_bonus.c \
				${BONUS_PARSER_PATH}/parser_lists_bonus.c \
				${BONUS_PARSER_PATH}/redir_lists_bonus.c \
				${BONUS_PARSER_PATH}/check_syntax_bonus.c

BONUS_EXPANSION := ${BONUS_EXPANSION_PATH}/expansion_bonus.c \
				   ${BONUS_EXPANSION_PATH}/expansion_utils_bonus.c \
				   ${BONUS_EXPANSION_PATH}/append_args_bonus.c \
				   ${BONUS_EXPANSION_PATH}/quote_cleaner_bonus.c \
				   ${BONUS_EXPANSION_PATH}/wildcard_bonus.c \
				   ${BONUS_EXPANSION_PATH}/wildcard_redir_bonus.c

BONUS_ENV := ${BONUS_ENV_PATH}/env_bonus.c \
			 ${BONUS_ENV_PATH}/env_lists_bonus.c

BONUS_HEREDOC := ${BONUS_HEREDOC_PATH}/heredoc_bonus.c \
				 ${BONUS_HEREDOC_PATH}/heredoc_signals_bonus.c

BONUS_EXECUTION := ${BONUS_EXECUTION_PATH}/execution_bonus.c \
				   ${BONUS_EXECUTION_PATH}/execution_utils_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/cd_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/echo_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/env_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/exit_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/export_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/pwd_bonus.c \
				   ${BONUS_EXECUTION_PATH}/builtins/unset_bonus.c \
				   ${BONUS_EXECUTION_PATH}/pipe/pipe_bonus.c \
				   ${BONUS_EXECUTION_PATH}/redirection/redir_bonus.c \
				   ${BONUS_EXECUTION_PATH}/redirection/ambiguous_redir_bonus.c

BONUS_SRC := ${BONUS_UTILS} \
			 ${BONUS_LEXER} \
			 ${BONUS_PARSER} \
			 ${BONUS_EXPANSION} \
			 ${BONUS_ENV} \
			 ${BONUS_HEREDOC} \
			 ${BONUS_EXECUTION} \
			 ${BONUS}/src/minishell_bonus.c \
			 ${BONUS}/src/minishell_utils_bonus.c

BONUS_OBJS := ${BONUS_SRC:.c=.o}

# ============ RULES ============
all: ${NAME}

${NAME}: ${OBJS} ${MANDO_INC}/minishell.h
	@printf "$(GREEN)  Linking $(NAME)...$(RESET)\n"
	@${CC} ${CFLAGS} ${OBJS} ${LIB_RL} -o ${NAME}
	@${RM} ${BONUS_OBJS}
	@printf "$(GREEN)  Successfully built $(NAME)$(RESET)\n"

bonus: .bonus

.bonus: ${BONUS_OBJS} ${BONUS_INC}/*_bonus.h
	@printf "$(GREEN)  Linking bonus $(NAME)...$(RESET)\n"
	@${CC} ${CFLAGS} ${BONUS_OBJS} ${LIB_RL} -o ${NAME}
	@touch .bonus
	@${RM} ${OBJS}
	@printf "$(GREEN)  Successfully built $(NAME)$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)  Compiling $<...$(RESET)\n"
	@${CC} ${CFLAGS} ${INCLUDE_RL} -c $< -o $@

clean:
	@printf "$(RED)  Cleaning object files...$(RESET)\n"
	@${RM} ${OBJS} ${BONUS_OBJS} .bonus
	@printf "$(GREEN)  Object files removed$(RESET)\n"

fclean: clean
	@printf "$(RED)  Removing executable...$(RESET)\n"
	@${RM} ${NAME}
	@printf "$(GREEN)  Executable file removed$(RESET)\n"

re: fclean all
	@printf "$(YELLOW)  Rebuilding project...$(RESET)\n"

.PHONY: all clean fclean re bonus
