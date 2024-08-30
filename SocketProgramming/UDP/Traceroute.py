import socket
import time
import struct
import os
import select

ICMP_ECHO_REQUEST = 8 # platform specific

def do_checksum(source_string):
    # Verify the packet integritity
    sum = 0
    max_count = (len(source_string)//2)*2
    count = 0

    while count < max_count:
        val = source_string[count + 1]*256 + source_string[count]                   
        sum = sum + val
        sum = sum & 0xffffffff 
        count = count + 2

    if max_count<len(source_string):
        sum = sum + ord(source_string[len(source_string) - 1])
        sum = sum & 0xffffffff 

    sum = (sum >> 16)  +  (sum & 0xffff)
    sum = sum + (sum >> 16)
    answer = ~sum
    answer = answer & 0xffff
    answer = answer >> 8 | (answer << 8 & 0xff00)
    return answer

def create_ICMPpacket(type, code, ID, sequence):
    # Create a dummy heder with a 0 checksum.
    my_checksum = 0
    header = struct.pack("bbHHh", type, code, my_checksum, ID, sequence)

    # Fill the ICMP's data field with some dummy information
    bytes_In_double = struct.calcsize("d")
    data = (192 - bytes_In_double) * "Q"
    data = struct.pack("d", time.time()) + bytes(data.encode('utf-8'))

    # Get the checksum on the data and the dummy header.
    my_checksum = do_checksum(header + data)
    header = struct.pack("bbHHh", type, code, socket.htons(my_checksum), ID, sequence)
    packet = header + data
    return packet

def traceroute(destination, max_hops=30, timeout=1):
    dest_addr = socket.gethostbyname(destination)
    ID = os.getpid() & 0xFFFF

    for ttl in range(1, max_hops + 1):
        for i in range(3):
            recv_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
            send_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
            send_socket.setsockopt(socket.SOL_IP, socket.IP_TTL, ttl)
            recv_socket.settimeout(timeout)
            recv_socket.bind(("", 0))

            packet = create_ICMPpacket(ICMP_ECHO_REQUEST, 0, ID, i)
            send_time = time.time()
            send_socket.sendto(packet, (dest_addr, 1))

            curr_addr = None
            curr_name = None
            try:
                ready = select.select([recv_socket], [], [], timeout)
                if ready[0] == []:
                    raise socket.error

                recv_time = time.time()
                recv_packet, addr = recv_socket.recvfrom(512)
                curr_addr = addr[0]
                try:
                    curr_name = socket.gethostbyaddr(curr_addr)[0]
                except socket.error:
                    curr_name = curr_addr

                rtt = (recv_time - send_time) * 1000
                if i == 0:
                    print(f'{ttl} {curr_name} ({curr_addr})', end=' ')
                
                print(f'{rtt:.3f}', end=' ')

            except socket.error:
                print(f'{ttl} * * *')

            finally:
                send_socket.close()
                recv_socket.close()

        print()

        if curr_addr == dest_addr:
            return

if __name__ == "__main__":
    destination = '140.114.89.43'
    traceroute(destination)