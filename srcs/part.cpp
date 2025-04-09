#include "../includes/all.hpp"

void	Server::PART(int fd, std::deque<std::string> cmd){
    _nbCliChannel[cmd[1]].erase(fd);
    // _channels[cmd[1]]->erase(fd);
}