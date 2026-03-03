# ft_irc

An IRC server that handles concurrent clients with no threads — just `poll()`, one loop, and careful buffer management. Written in C++98.

## Quick Start

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

**I/O multiplexing with `poll()`**

The server monitors all file descriptors — the listening socket and every connected client — in a single `poll()` call. No threads, no blocking reads. When a descriptor is ready, the server reads available bytes into that client's buffer, then processes complete messages line by line.

This means the entire server runs in one thread. No mutexes, no race conditions, no context switches. The tradeoff is that any slow operation in a handler blocks all clients — so handlers stay fast.

**Message parsing**

Each IRC message follows the format `[:prefix] COMMAND [params] [:\trailing]`. The parser extracts the command and its arguments, then dispatches to a handler. Unknown commands get a 421 error reply; malformed messages are silently dropped.

**State management**

The server tracks clients (nickname, username, channels, operator status) and channels (topic, modes, member list) in maps. When a client disconnects, they're removed from all channels and the client map.

**C++98 constraint**

No lambdas, no smart pointers, no `auto`, no range-based loops. Every resource allocation has a matching deallocation. The Orthodox Canonical Form is enforced throughout. Writing C++98 is the fastest way to understand what RAII and move semantics actually solve.

## Supported commands

`NICK` `USER` `PASS` `JOIN` `PART` `PRIVMSG` `NOTICE` `KICK` `INVITE` `TOPIC` `MODE` `QUIT`

**Channel modes:** `+i` (invite-only) `+t` (topic restricted) `+k` (password) `+o` (operator) `+l` (user limit)

## Project structure

```
├── includes/     — Server, Client, Channel class headers
└── srcs/         — server loop, command handlers, message parsing, utils
```
