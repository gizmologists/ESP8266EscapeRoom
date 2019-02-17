# ESP8266 Escape Room Wifi
The server and client code for Gizmologists escape room.

Code in `escape-room-server.py` will be run on a Raspberry Pi to be communicated with ESP8266-01 chips.  Code in the Arduino libraries runs on Arduinos to communicate with it.

## Protocol
All requests and responses are 7 bytes.

### Requests
Format: `puzzle_code command`

`puzzle_code` - The puzzle of the request
 - `MRS`: Morse code puzzle
 - `BKS`: Books puzzle
 - `TIM`: Time machine puzzle
 - `GRS`: Gears puzzle

`command` - The command to run
 - `DNE`: Mark puzzle as done
 - `RST`: Reset puzzle to incomplete
 - `GET`: Get status of puzzle

Example requests:
 - `MRS DNE`: Mark the morse code puzzle as done
 - `BKS GET`: Get the status of the books puzzle

### Responses

Format: `puzzle_code status`

`puzzle_code` - The puzzle of the request (same codes as request)

`status` - Status of the puzzle AFTER the request is processed (same codes as request)

Response will be `INVALID` if command was invalid in any way.
