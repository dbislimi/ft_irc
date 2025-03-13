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

int	Client::getFd() const{
    return (this->_fd);
}

void Client::setSign(bool isSign){
    this->_isSigned = isSign;
}

bool Client::getSign(){
    return (_isSigned);
}

void Client::setBoolName(bool allName){
    this->_allName = allName;
}

bool Client::getBoolName(){
    return (_allName);
}

void Client::setNickName(std::string nickName){
    this->_nickName = nickName;
}

void Client::setUserName(std::string userName){
    this->_userName = userName;
}

std::string Client::getNickName() const{
    return (_nickName);
}

std::string Client::getUserName() const{
    return (_userName);
}
