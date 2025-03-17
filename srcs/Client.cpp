#include "../includes/Client.hpp"

void    Client::setFd(int fd){
    this->_fd = fd;
}

void Client::setIpAdd(struct in_addr addr){
	char buffer[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr.s_addr, buffer, sizeof buffer);
    this->_ip = buffer;
    std::cout <<"ip: " << this->_ip << std::endl;
}

const std::string&	Client::getIp() const{
    return (this->_ip);
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

bool	Client::isConnected() const{
    return (this->_isConnected);
}

void    Client::connect(){
    this->_isConnected = true;
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

void Client::setBoolName(bool allName){
    this->_allName = allName;
}

bool Client::getBoolName(){
    return (_allName);
}

void	Client::setChannel(std::string& name){
    this->_channel = name;
}
std::string	Client::getChannel() const{
    return (_channel);
}