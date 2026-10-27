from socket import *

def run_client():
    host = "127.0.0.1"
    port = 12000

    # create UDP socket
    client = socket(AF_INET, SOCK_DGRAM)

    try:
        msg = input("Enter a message (lowercase): ")

        # send data
        client.sendto(msg.encode(), (host, port))

        # receive response
        data, server_addr = client.recvfrom(2048)

        print("\nReply from server:")
        print("Address:", server_addr)
        print("Message:", data.decode())

    except Exception as e:
        print("Error:", e)

    finally:
        client.close()


if __name__ == "__main__":
    run_client()