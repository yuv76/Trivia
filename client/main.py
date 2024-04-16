import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 9090


def main():
    # Create a TCP socket for the client
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.connect((SERVER_IP, SERVER_PORT))

    # receive the server message
    server_msg = server_sock.recv(1024)
    server_msg = server_msg.decode()
    print(server_msg)

    # send the clients message to the server
    client_msg = "Hello"
    try:
        server_sock.sendall(client_msg.encode())
        server_sock.close()

    except ConnectionResetError as error:
        print("the connection was cut", error)

        return 0


if __name__ == "__main__":
    main()
