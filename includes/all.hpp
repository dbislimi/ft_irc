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
# define BACKLOG 10 // nombre max de demandes de connexion

#define BLD std::string("\002")  // Bold (Gras)

#define WHT std::string("\00300")  // White
#define BLK std::string("\00301")  // Black
#define BLU std::string("\00302")  // Navy Blue
#define GRE std::string("\00303")  // Green
#define RED std::string("\00304")  // Red
#define BRN std::string("\00305")  // Brown
#define VIO std::string("\00306")  // Violet
#define ORG std::string("\00307")  // Orange
#define YEL std::string("\00308")  // Yellow
#define LGR std::string("\00309")  // Light Green
#define LCY std::string("\00310")  // Light Cyan
#define LBL std::string("\00311")  // Light Blue
#define DBL std::string("\00312")  // Blue (Deep Blue pour éviter conflit avec BLU)
#define PIN std::string("\00313")  // Pink
#define LGY std::string("\00314")  // Light Gray
#define DGY std::string("\00315")  // Dark Gray

#define RST std::string("\017")    // Reset

class Client;
class Channel;
class Server;

# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"