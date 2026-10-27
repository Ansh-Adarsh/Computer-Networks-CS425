from socket import *

def start_server():
    host = "127.0.0.1"
    port = 12000

    # create UDP socket
    server = socket(AF_INET, SOCK_DGRAM)
    server.bind((host, port))

    print("UDP Server is active on port", port)

    while True:
        try:
            data, client_addr = server.recvfrom(2048)

            print("\nClient connected:", client_addr)
            received_text = data.decode()
            print("Received data:", received_text)

            # process data (convert to uppercase + add tag)
            response = "[Processed] " + received_text.upper()

            server.sendto(response.encode(), client_addr)

        except Exception as e:
            print("Server error:", e)


if __name__ == "__main__":
    start_server()