import socket
import binascii
import struct

SERVER_IP = "127.0.0.1"
SERVER_PORT = 9090


def menu():
    signup = True
    print("Enter 1 for login, else will sign up")
    choice = str(input())

    if input == "1":
        signup = False

    return signup

def main():
    # Create a TCP socket for the client
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.connect((SERVER_IP, SERVER_PORT))

    is_signup = menu()

    msg = ""
    code = 2
    if is_signup:
        code = 1
    msg += chr(code)

    json = '{'
    username = input("Enter Username: ")
    json += '"username"'
    json += username
    password = input("Enter password: ")
    json += '"password"'
    json += password
    mail = ""
    if is_signup:
        mail = input("Enter mail: ")
        json += '"email"'
        json += mail
    json += '}'

    length = len(json)
    print(length)
    bytes_len = struct.pack(">i", length)
    for i in bytes_len:
        msg += chr(i)

    msg += json

    # send the client message to the server
    try:
        server_sock.sendall(msg.encode())
        print(msg)

    except ConnectionResetError as error:
        print("the connection was cut", error)

    # receive the server message
    server_msg = server_sock.recv(1024)
    server_msg = server_msg.decode()
    print(server_msg)
    server_sock.close()


if __name__ == "__main__":
    main()
