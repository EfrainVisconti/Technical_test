NAME		=	Even_odd

DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Werror -Wextra -g3 -pthread

SRC_FILES	=	main check_args parse_file run_program threads node utils
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRC_DIR = src/
OBJ_DIR = obj/

all: $(NAME)

$(NAME):$(OBJ)
		@$(CC) $(OBJ) $(CCFLAGS) -o $(NAME)
		@echo "Even_odd have been compiled!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaning objects..."

fclean: clean
	@$(RM) $(NAME)
	@echo "Removing the executable..."

re: fclean all

.PHONY: all clean fclean re