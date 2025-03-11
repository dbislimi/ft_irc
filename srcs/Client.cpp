#include "../includes/Client.hpp"

void    Client::setFd(int fd){
    this->_fd = fd;
}

void Client::setIpAdd(struct in_addr addr){
    this->addr = addr;
}
const struct in_addr&	Client::getIp() const{
    return (this->addr);
}