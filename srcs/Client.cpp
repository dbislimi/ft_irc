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

void Client::setInvited(std::string nm, bool value){
    _invited[nm] = value;
}

void Client::insertInvited(std::string nm, bool val){
    _invited[nm] = val;
}

bool Client::getInvited(Channel c){
    for(std::map<std::string, bool>::iterator it = _invited.begin(); it != _invited.end(); ++it){
        if (it->first == c.getName()){
            return it->second;
        }
    }
    return false;
}

void Client::setInvited(std::string nm, bool value){
    _invited[nm] = value;
}

void Client::insertInvited(std::string nm, bool val){
    _invited[nm] = val;
}

bool Client::getInvited(Channel c){
    for(std::map<std::string, bool>::iterator it = _invited.begin(); it != _invited.end(); ++it){
        if (it->first == c.getName()){
            return it->second;
        }
    }
    return false;
}

bool Client::getRegister(){
    return (this->_isRegistered);
}

void Client::setRegister(){
    _isRegistered = true;
}

bool Client::getIsInvited(){
    return this->_isInvited;
}

void Client::setIsInvited(bool isInvited){
    this->_isInvited = isInvited;
}

time_t Client::getLastAction(){
    return _lastAction;
}

void Client::setLastAction(time_t lastAct){
    this->_lastAction = lastAct;
}

time_t Client::getLastPing(){
    return _lastPing;
}

void Client::setLastPing(time_t lastPing){
    this->_lastPing = lastPing;
}

time_t Client::getLastPong(){
    return _lastPong;
}

void Client::setLastPong(time_t lastPong){
    this->_lastPong = lastPong;
}

bool Client::getStartedPing() const{
    return this->_startToPing;
}

void Client::setStartedPing(bool startPing){
    this->_startToPing = startPing;
}