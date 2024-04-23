import socket
import struct
import ubjson

SERVER_IP = "127.0.0.1"
SERVER_PORT = 9090

HEADER_LEN = 5


def menu():
    signup = True
    print("Enter 1 for login, else will sign up")
    choice = str(input())

    if choice == '1':
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

    username = input("Enter Username: ")
    password = input("Enter password: ")
    mail = ""
    j = {'username': username, 'password': password}
    if is_signup:
        mail = input("Enter mail: ")
        j["email"] = mail

    e = ubjson.dumpb(j)

    length = len(e)

    bytes_len = struct.pack(">i", length)  # convert to 4 bytes
    for i in bytes_len:
        msg += chr(i)
    for j in e:
        msg += chr(j)

    # send the client message to the server
    try:
        server_sock.sendall(msg.encode())

    except ConnectionResetError as error:
        print("the connection was cut", error)

    # receive the server message
    server_header = server_sock.recv(5)  # get header
    server_header = server_header.decode()

    full_msg = server_sock.recv(1024)  # entire message (in a large buffer for now)
    ans = ubjson.loadb(full_msg)
    print(ans)

    server_sock.close()


if __name__ == "__main__":
    main()
