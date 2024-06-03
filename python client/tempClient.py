import socket
import struct
import ubjson

SERVER_IP = "127.0.0.1"
SERVER_PORT = 9090

HEADER_LEN = 5


def signup_check():
    # adding a new user to add another one later to see what happens when a user already exists
    j = {'username': 'abi', 'password': 'abdul', 'email': 'abi.abdul@hmail.com'}

    # Create a TCP socket for the client
    server_sock1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock1.connect((SERVER_IP, SERVER_PORT))

    msg = ""
    code = 1
    msg += chr(code)
    e = ubjson.dumpb(j)
    length = len(e)
    bytes_len = struct.pack(">i", length)  # convert to 4 bytes
    for i in bytes_len:
        msg += chr(i)
    for j in e:
        msg += chr(j)

    # send the client message to the server
    try:
        server_sock1.sendall(msg.encode())

    except ConnectionResetError as error:
        print("the connection was cut", error)

    # receive the server message
    server_header = server_sock1.recv(5)  # get header
    server_header = server_header.decode()
    full_msg = server_sock1.recv(1024)  # entire message (in a large buffer for now)
    ans = ubjson.loadb(full_msg)
    server_sock1.close()

    return j


def menu():
    signup = True
    print("Enter 1 for login, else will sign up")
    choice = str(input())

    if choice == '1':
        signup = False

    return signup


def check_menu():
    code = 2
    msg = ""
    is_signup = False

    print("Enter 1 for a signup check\n2 for a login check with a nonexistent user\n3 for a login check with the wrong password\n4 for a login check with a user that's already connected\nelse will go to the regular menu")
    choice = str(input())
    if choice == '1':
        j = {'username': 'glila', 'password': '12345', 'email': 'glila.golani@hmail.com'}
        code = 1
        is_signup = True
    elif choice == '2':
        j = {'username': 'lola', 'password': 'show'}
    elif choice == '3':
        j = signup_check()
        j = {'username': 'abi', 'password': '1234'}
    elif choice == '4':
        j = signup_check()
        j = {'username': 'abi', 'password': 'abdul', 'email': 'abi.abdul@hmail.com'}
    else:
        is_signup = menu()
        if is_signup:
            code = 1
        username = input("Enter Username: ")
        password = input("Enter password: ")
        mail = ""
        j = {'username': username, 'password': password}
        if is_signup:
            mail = input("Enter mail: ")
            j["email"] = mail

    msg += chr(code)

    return j, msg, is_signup


def main():
    # Create a TCP socket for the client
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.connect((SERVER_IP, SERVER_PORT))

    j, msg, is_signup = check_menu()

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

    if is_signup:
        if ans == {'status': 1}:
            print("signup was successful.")
        if ans == {'status': 0}:
            print("signup was not successful - username is already used.")
    else:
        if ans == {'status': 1}:
            print("login was successful.")
        if ans == {'status': 0}:
            print("login was not successful - wrong password.")
        if ans == {'status': 2}:
            print("login was not successful - username does not exist.")
        if ans == {'status': 3}:
            print("login was not successful - user is already connected.")

    server_sock.close()


if __name__ == "__main__":
    main()
