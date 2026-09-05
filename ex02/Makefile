NAME = PmergeMe

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -I include

SRC_DIR = src/
OBJ_DIR = obj/

SRC =	$(addprefix $(SRC_DIR), main.cpp \
								PmergeMe.cpp)
OBJS = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "$(GREEN)[Compiling]$(NC) $(notdir $(<))...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[Cleaning]$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re