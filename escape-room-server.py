# Escape room wifi server
# Served from port 1337
# Protocol:
#
# All requests must be 7 characters with 2x 3 letter codes
#
# Each puzzle has 3 letter code:
#   Morse: MRS
#   Books: BKS
#   Time machine: TIM
#   Gears: GRS
#
# Given 3 letter code, 3 letter code follows after a space to indicate request
#   DNE: Mark puzzle as done on server and Adafruit
#   GET: Get the status of puzzle
#   RST: Mark puzzle as NOT done on server and Adafruit
#
# Example requests:
#   MRS DNE: Change morse code status to complete
#   TIM RST: Change time machine status to incomplete
#   BKS GET: Get status of book puzzle
#
# Given a request, this server responds in a 7 byte code as follows:
#   puzzle_code status
# Where puzzle_code is the puzzle passed in and status is DNE for done or RST for not done
#   BKS DNE: Means books puzzle is done
#
# Note this means DNE commands should always return the puzzle name then DNE
# and RST commands always return puzzle name then RST
# GET commands will return the status, either DNE (done) or RST (incomplete)
#
# Invalid commands are responded to with INVALID

import socket
from Adafruit_IO import *

aio = Client('ogreatfox', '8341795c01774027901eae1c9f822f2d')

PUZZLE_FEEDS = {
    "MRS": "morse-feed",
    "TIM": "time-feed",
    "BKS": "books-feed",
    "GRS": "gears-feed"
}

status = {}

def puzzle_done(puzzle):
    print("done", puzzle)
    data = aio.receive(PUZZLE_FEEDS[puzzle])
    data = data.value.split()
    aio.send(PUZZLE_FEEDS[puzzle], str(data[0]) + " DNE")
    status[puzzle] = "DNE"
    return puzzle + " DNE"


def puzzle_get(puzzle):
    print("get", puzzle)
    return puzzle + " " + status[puzzle]


def puzzle_reset(puzzle):
    print("reset", puzzle)
    data = aio.receive(PUZZLE_FEEDS[puzzle])
    data = data.value.split()
    aio.send(PUZZLE_FEEDS[puzzle], str(data[0]) + " RST")
    status[puzzle] = "RST"
    return puzzle + " RST"


PORT = 1337

COMMAND_FUNCTIONS = {
    "DNE": puzzle_done,
    "GET": puzzle_get,
    "RST": puzzle_reset
}

for feed in list(PUZZLE_FEEDS.keys()):
    data = aio.receive(PUZZLE_FEEDS[feed]).value.split()
    status[feed] = data[1]

print("Puzzle statuses: ", status)

# Setup socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", PORT))

while True:
    s.listen(1)
    conn, addr = s.accept()
    # Connection received, process connection
    # We know that nothing will be more than 16 bytes (not even more than 8 but you know)
    # So why not just limit it to that? :)
    data = conn.recv(16).decode()
    try:
        puzzle, command = data.split()
        if puzzle not in PUZZLE_FEEDS or command not in COMMAND_FUNCTIONS:
            print("Invalid command received:", data)
            conn.send("INVALID".encode())
            conn.close()
            continue
    # Don't repeat yourself? Well too bad.
    except ValueError:
        print("Invalid command received:", data)
        conn.send("INVALID".encode())
        conn.close()
        continue

    response = COMMAND_FUNCTIONS[command](puzzle)
    conn.send(response.encode())
    conn.close()
    print("Connection processed successfully")
