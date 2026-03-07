# ft_irc

IRC server written in C++98. Uses `poll()` for I/O multiplexing, so everything runs in a single thread with no blocking.

## Build

```bash
make
./ircserv <port> <password>
```

Connect with any IRC client:

```bash
irssi -c localhost -p <port>
# or with netcat for testing
nc localhost <port>
```

## How it works

The server uses `poll()` to monitor the listening socket and all connected clients in one call. When data is available on a socket, it's read into that client's buffer and processed line by line once a complete message arrives.

Each IRC message is parsed as `[:prefix] COMMAND [params] [:trailing]`. The command gets dispatched to a handler. Unknown commands get a 421 reply.

The server tracks clients (nick, user, channels, operator status) and channels (topic, modes, members) in maps. Disconnecting clients are cleaned up from everything.

C++98 means no smart pointers, no lambdas, no auto. Resource management is manual, Orthodox Canonical Form used throughout.

## Commands

`NICK` `USER` `PASS` `JOIN` `PART` `PRIVMSG` `KICK` `INVITE` `TOPIC` `MODE` `QUIT`

**Channel modes:** `+i` (invite-only) `+t` (topic restricted) `+k` (password) `+o` (operator) `+l` (user limit)

## Structure

```
├── includes/     - Server, Client, Channel class headers
└── srcs/         - server loop, command handlers, parsing, utils
```
