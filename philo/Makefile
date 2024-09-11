NAME = philo
OBJ_DIR = build
CFLAGS = -g -Wall -Wextra -Werror
SRC_DIR = src
CC = gcc
SRC = $(SRC_DIR)/util.c philo.c
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "Philosophers compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)/*.o

fclean: clean
	@$(RM) $(NAME)

re: fclean all