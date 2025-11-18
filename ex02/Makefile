NAME = PmergeMe

CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98

FILENAMES = main PmergeMe
SOURCES = $(addsuffix .cpp, $(FILENAMES))
OBJECTS = $(addsuffix .o, $(FILENAMES))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CPP) $(CPP_FLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re