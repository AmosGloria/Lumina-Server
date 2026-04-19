# Lumina-Server# Lumina-Server
A lightweight, high-performance HTTP server built from scratch in C.

## Overview
Built to explore the underlying infrastructure of the web, Lumina-Server uses the **Berkeley Sockets API** to handle TCP/IP connections and manually serves web content from the local file system.

## Features
- **Socket Programming:** Implements `socket`, `bind`, `listen`, and `accept`.
- **Memory Management:** Manual allocation using `malloc` and `free` for file buffers.
- **File I/O:** Efficiently reads and streams HTML content to the browser.

## How to Run
1. Open terminal in a Linux environment (or Codespaces).
2. Run `make` to compile.
3. Run `./lumina`.
4. Visit `http://localhost:8080` in your browser.