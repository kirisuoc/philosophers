NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra

# Directorios
SRC_DIR = src
INCLUDE_DIR = includes

# Colores
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
CYAN = \033[36m
RESET = \033[0m

# Archivos fuente y objetos
SRC = $(addprefix $(SRC_DIR)/, main.c)
OBJ = $(SRC:.c=.o)

# Regla principal
all: $(NAME)

# Regla para compilar el ejecutable
$(NAME): $(OBJ)
	@echo "$(GREEN)Construyendo $(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Reglas para limpiar los archivos objeto
clean:
	@echo "$(RED)Limpiando archivos objeto$(RESET)"
	rm -rf $(OBJ)

fclean: clean
	@echo "$(RED)Limpiando $(NAME)$(RESET)"
	rm -rf $(NAME)

# Regla para recompilar todo
re: fclean all
	@echo "$(YELLOW)Recompilando todo$(RESET)"
