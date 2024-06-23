
Project structure:

/home/abjijit/tcp_load_balancer

    ├── CMakeLists.txt
    
    ├── build
    
    ├── include
    
    │   ├── Client.h
    
    │   ├── Server.h
    
    │   └── LoadBalancer.h
    
    └── src
    
        ├── Client.cpp
        
        ├── Server.cpp
        
        ├── LoadBalancer.cpp
        
        └── main.cpp
        


### Project Summary: TCP-based Load Balancer System

#### Objective:
The objective of this project is to implement a TCP-based load balancer system using C++ with POSIX sockets. The system consists of multiple components: clients, servers, and a load balancer. The load balancer distributes incoming client requests among multiple backend servers, achieving load distribution and fault tolerance.

#### Components:
1. **Client**:
   - **Functionality**: Initiates TCP connections to the load balancer.
   - **Operations**: Sends requests to the load balancer and receives responses from backend servers.

2. **Server**:
   - **Functionality**: Listens for incoming TCP connections from clients.
   - **Operations**: Handles client connections, reads client requests, and sends back responses.

3. **Load Balancer**:
   - **Functionality**: Listens for incoming client connections and distributes them among backend servers.
   - **Operations**: Uses round-robin or another scheduling algorithm to balance load across servers. It maintains connections with backend servers and forwards requests from clients to appropriate servers based on load balancing rules.

#### Implementation Details:
- **Client (`Client.cpp`, `Client.h`)**:
  - Establishes a TCP connection to the load balancer.
  - Sends requests to the load balancer and prints server responses.

- **Server (`Server.cpp`, `Server.h`)**:
  - Listens on a specified port for incoming client connections.
  - Reads client messages, prints them to console for debugging, and sends a fixed response back to the client.

- **Load Balancer (`LoadBalancer.cpp`, `LoadBalancer.h`)**:
  - Listens on a specified port for incoming client connections.
  - Maintains connections with backend servers.
  - Implements load balancing logic (round-robin) to forward client requests to backend servers.
  - Receives responses from backend servers and forwards them back to clients.

- **Main Program (`main.cpp`)**:
  - Initializes and starts multiple instances of servers, a load balancer, and clients using threads (`std::thread`).
  - Demonstrates concurrent operation of servers, load balancer, and clients.
  - Configures backend server addresses and ports for the load balancer.

#### Execution Flow:
1. **Backend Servers Initialization**:
   - Two backend servers are started on ports `8081` and `8082` using separate threads.

2. **Load Balancer Initialization**:
   - The load balancer starts listening on port `8080` and maintains connections with backend servers (`127.0.0.1:8081` and `127.0.0.1:8082`).

3. **Client Operations**:
   - Two clients connect to the load balancer (`127.0.0.1:8080`) and send messages (`"Hello from client 1"` and `"Hello from client 2"`).

4. **Concurrency and Synchronization**:
   - Threads are managed to ensure that all components (servers, load balancer, and clients) operate concurrently and handle communication properly.

#### Conclusion:
This project demonstrates the implementation of a TCP-based load balancer system using C++ and POSIX sockets. It emphasizes concepts such as socket programming, multi-threading, client-server communication, and load balancing algorithms. The system is designed to efficiently distribute client requests among multiple servers, ensuring scalability and fault tolerance in handling network traffic.
