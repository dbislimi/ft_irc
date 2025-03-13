SRCS_PATH = ./srcs
SRCS = ${addprefix ./srcs/, main.cpp Server.cpp Client.cpp Channel.cpp utils.cpp}
OBJS = $(SRCS:.cpp=.o)

NAME 		= ircserv
CC 			= c++
CPPFLAGS 	= -Wall -Wextra -Werror -std=c++11 -g3
RM 			= rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re