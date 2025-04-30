#pragma once

# include <algorithm>
# include <exception>
# include <cstring>
# include <sstream>
# include <cstdlib>
# include <unistd.h>
# include <cstdio>
# include <fcntl.h>
# include <poll.h>
# include <iostream>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
# include <vector>
# include <ctime>

# include <csignal>
# include <map>
# include <set>
# include <deque>
# define INT_MAX 2147483647
# define BACKLOG 10

class Client;
class Channel;
class Server;

# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"