NAME = webserv

CC = c++

CFLAGS = -Werror -Wall -Wextra -std=c++98

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = $(notdir $(wildcard $(SRC_DIR)*.cpp))
OBJ_FILES = $(SRC_FILES:.cpp=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INCLUDES = include/

all : obj $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDES) -o $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

clean :
	@$(RM) $(OBJ_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
