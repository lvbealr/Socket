<p align="center">
  <a href="" rel="noopener">
 <img src="https://i.imgur.com/H67OZIu.png" alt="Project logo"></a>
</p>

## 📝 Table of Contents

- [About](#about)
- [How It Works](#how_it_works)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting_started)
- [Example Usage](#usage)
- [Built Using](#built_using)
- [Authors](#authors)

---

## 🧐 About <a name = "about"></a>

This project consists of a **Server** and **Client** application, where:

- **Server** is implemented in `server.cpp` and `server.h`, and a binary executable (`mksock`) responsible for listening to incoming connections and echoing messages back to the client.
- **Client** consists of `client.cpp`, `client.h`, and a binary executable (`client`) that allows users to send messages to the server.

---

## 🔄 How It Works <a name = "how_it_works"></a>

### Server (Server Side)
The server listens on a specified port and waits for incoming messages from the client. When a message is received, the server echoes the message back.

1. The server uses **sockets** to establish a communication channel.
2. Once connected, it waits for a message.
3. Upon receiving the message, the server sends the same message back to the client.

### Client (Client Side)
The client connects to the server and sends messages that it wants echoed back.

1. The client runs a command-line interface where users can type messages.
2. The client connects to the server and sends the typed message.
3. The server processes and sends the message back, which is displayed on the client's terminal.

### 🏗 Architecture Diagram 

<p align="center">
  <a href="" rel="noopener">
 <img src="https://i.imgur.com/Qr1lOum.png" alt="Project logo"></a>
</p>

---

## 📂 File Structure 

```
Socket/
│
├── server/
│   ├── server.cpp   # Server implementation
│   ├── server.h     # Server header file
│   └── mksock       # Script to launch the echo server
│
├── client/
│   ├── client.cpp   # Client implementation
│   ├── client.h     # Client header file
│   └── client       # Binary file to launch the client
│
└── README.md        # This README file
```

### Server
- **server.cpp**: Contains the logic to create a socket, bind, listen, accept connections, and echo messages back.
- **server.h**: Header file with declarations for the server functions.
- **mksock**: A helper file to launch the echo server.

### Client
- **client.cpp**: Client-side application that connects to the server and sends messages.
- **client.h**: Header file containing declarations for the client-side functions.
- **client**: Executable file to run the client program.

---

## 🛠️ Prerequisites <a name = "prerequisites"></a>
- A C++ compiler (e.g., `g++`)
- CMake (for building)
- A terminal or command line interface

---

## 🏁 Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development.

### Clone Repository

To get started, simply clone this repository and build both the server and client applications.

```bash
git clone git@github.com:lvbealr/Socket.git
cd Socket/
```

### Build and Using

First of all, initialize submodule <b>customWarning</b> and <b>colorPrint</b>.

```bash
git submodule update --init --remote --recursive
```
You can use <b>CMake</b> to build the program and run it.

Enter the following command in the terminal:

```bash
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build && cd build && make
```

Once compiled you can run the executable with the following command.

Launch the server from a one terminal:

```bash
./server/mksock [path-to-socket-file]
```
and the client from another terminal:

```bash
./client/client [path-to-socket-file]
```
Remember that the server must be running before the client.

---

## 💬 Example Usage <a name="usage"></a>

<p align="center">
  <a href="" rel="noopener">
 <img src="https://github.com/lvbealr/Socket/blob/main/docs/socket.gif" alt="Socket Gif"></a>
</p>

---

## ⛏ Built Using <a name = "built_using"></a>

- [customWarning](https://github.com/lvbealr/customWarning) - Warning Module
- [colorPrint](https://github.com/lvbealr/colorPrint) - Module For Colourful Print

---

## ✍ Authors <a name = "authors"></a>

- [@lvbealr](https://github.com/lvbealr) - Idea & Initial work
