import socket
import pynmea2


# --------------------------------------------------------------------------------------------------
def get_GPS_fix(socket):
    """
        Read a GPS message via TCP socket.
        We are looking for $GPGGA, which contains Time, position, and fix related data.

        Read more:
        https://www.trimble.com/OEM_ReceiverHelp/V4.44/en/NMEA-0183messages_GGA.html
    """

    chars = []

    while True:
        # read bytes from socket
        c = socket.recv(1).decode('utf-8')
        chars.append(c)

        # found endline
        if c == '\n':
            line = ''.join(chars)

            # found a GGA type message
            if line.split(",")[0] == '$GPGGA':

                # parse the message
                gga = pynmea2.parse(line)

                # gps quality is good, position is valid
                if int(gga.data[gga.name_to_idx['gps_qual']]) >= 1:
                    return gga
                else:
                    chars = []
            # drop other types of messages
            else:
                chars = []


# --------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    HOST = '192.168.1.2'
    PORT = 6000

    # connect to gps socket server (phone)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        print("Connecting to socket...")
        s.connect((HOST, PORT))
        print("Listening to GPS messages...")
    except ConnectionRefusedError:
        print("Connection failed!")
    except TimeoutError:
        print("Connection timed out!")
        exit()

    # read a few gps positions
    for _ in range(4):
        gga = get_GPS_fix(s)
        t = gga.data[0]
        print(
            "Got GPS fix at @{}, ({:.6f}, {:.6f})".format(
                ':'.join([t[0:2], t[2:4], t[4:6]]),
                gga.latitude,
                gga.longitude
            )
        )
