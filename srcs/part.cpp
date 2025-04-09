#include "../includes/all.hpp"

void	Server::PART(int fd, std::deque<std::string> cmd){
    sendChannel(-1, cmd[1], ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" +  _clients[fd]->getIp() + " PART " + cmd[1] + " :Leaving\r\n");
    _channels[cmd[1]]->removeOp(fd);
    _nbCliChannel[cmd[1]].erase(_clients[fd]->getNickName());
}