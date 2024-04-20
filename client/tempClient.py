import socket
import binascii

SERVER_IP = "127.0.0.1"
SERVER_PORT = 9090


def menu():
    signup = True
    print("Enter 1 for login, else will sign up")
    choice = input()
    
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
    bin_code = binary_string = bin(code)[2:].zfill(8)
    msg = bin_code

    username = input("Enter Username: ")
    password = input("Enter password: ")
    mail = ""
    if is_signup:
        mail = input("Enter mail: ")
    hex_string = binascii.hexlify(string_to_convert.encode())

    # Convert the hexadecimal string to binary format
    binary_string = binascii.unhexlify(hex_string)

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
