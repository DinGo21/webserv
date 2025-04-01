NAME = webserv

CC = c++

CFLAGS = -Werror -Wall -Wextra -std=c++98 -g
RM = rm -rf

SRC_DIR = src/
SRC = $(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)config/*.cpp) $(wildcard $(SRC_DIR)monitor/*.cpp)
SRC_FILES = $(notdir $(SRC))

OBJ_DIR = obj/
OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))


INCLUDES = include/

all : obj $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)config/%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)monitor/%.cpp
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
