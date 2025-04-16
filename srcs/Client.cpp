#include "../includes/all.hpp"


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

void    Client::connect(){
    _server->intro(_fd);
    this->_isConnected = true;
}

bool	Client::isConnected() const{
    return (this->_isConnected);
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

std::string Client::getTempNick() const{
    return (_tempNick);
}

void Client::setBoolName(bool allName){
    this->_allName = allName;
}

bool Client::getBoolName(){
    return (_allName);
}

void Client::setBoolOps(bool isOps){
    this->_isOps = isOps;
}

bool Client::getBoolOps(){
    return _isOps;
}

std::string    Client::getCat() const{
    return (_to_cat);
}

std::string	Client::cat(std::string buff){
	return (_to_cat += buff);
}

void	Client::clearCat(){
	_to_cat.clear();
}

void    Client::setTempNick(std::string nick){
    this->_tempNick = nick;
}

bool Client::getBoolNick(){
    return (this->_nick);
}

void Client::setBoolNick(){
    _nick = true;
}

/*bool Client::getIsopps(){
    return _isopps;
}

void Client::setIsopps(bool val){
    _isopps = val;
}*/
