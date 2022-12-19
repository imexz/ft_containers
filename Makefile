NAME1 = ft_containers
NAME2 = std_containers
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
SOURCES = ./tests/test3.cpp

all: $(NAME1) $(NAME2)

$(NAME1): $(SOURCES)
	$(CC) $(CPPFLAGS) $(SOURCES) -D FT -o $(NAME1)

$(NAME2): $(SOURCES)
	$(CC) $(CPPFLAGS) -D BUILD_STD $(SOURCES) -o $(NAME2)

clean:
	@$(RM) $(NAME1)
	@$(RM) $(NAME2)
	@rm -f ./tests/logs/output_ft1
	@rm -f ./tests/logs/output_ft2
	@rm -f ./tests/logs/output_ft3
	@rm -f ./tests/logs/output_std1
	@rm -f ./tests/logs/output_std2
	@rm -f ./tests/logs/output_std3
	@rm -f ./tests/logs/diff1.diff
	@rm -f ./tests/logs/diff2.diff
	@rm -f ./tests/logs/diff3.diff
	@rm -f ft_containers1
	@rm -f ft_containers2
	@rm -f ft_containers3
	@rm -f std_containers1
	@rm -f std_containers2
	@rm -f std_containers3

re: clean all
