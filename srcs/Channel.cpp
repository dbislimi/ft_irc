#include "../includes/all.hpp"


// void Channel::delete_user(int fd) {
//     for (size_t i = 0; i < _users.size(); ++i) {
//         if (_users[i] == fd) {
//             std::swap(_users[i], _users.back());
//             _users.pop_back();
//             break;
//         }
//     }
// }

// void	Channel::sendChannel(int fd, std::string msg){
// 	for (std::map<std::string, int>::iterator it = _users.begin(); it != _users.end(); ++it){
//         if (fd == -1 || it->second != fd)
// 			send(it->second, msg.c_str(), msg.length(), 0);
//     }
// }

bool	Channel::isOp(int fd){
	for (std::deque<int>::iterator it = _ops.begin(); it != _ops.end(); ++it)
		if (*it == fd)
			return (true);
	return (false);
}

// bool	Channel::findUser(std::string nick) {
// 	for (std::map<std::string, int>::iterator it = _users.begin(); it != _users.end(); ++it){
// 		if (it->first == nick)
// 			return (true);
// 	}
// 	return (false);
// }

void	Channel::removeOp(int fd){
	for (std::deque<int>::iterator it = _ops.begin(); it != _ops.end(); ++it){
		if (*it == fd){
			_ops.erase(it);
			return ;
		}
	}
}

