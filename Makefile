NAME= ircserv

CFLAGS= -Wall -Wextra -Werror -std=c++98 -I inc
CC= c++

SRCS= srcs/Server.cpp srcs/main.cpp srcs/Commands/Command.cpp srcs/Commands/CommandPass.cpp srcs/Commands/CommandManager.cpp
OBJS= $(SRCS:.cpp=.o)

all: $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re