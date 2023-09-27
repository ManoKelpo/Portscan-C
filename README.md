# Portscan-C
A quick portscanner made in C.

## Installation:
1. Clone the repo into your directory of choice `git clone https://github.com/ManoKelpo/Portscan-C.git`.
2. Enter the directory `cd Portscan-C`.
3. Type `make` and wait for it to compile.

## Usage:
 -To scan a single port:
  `./portscanc ip port` 

 -Scan a range of ports:
  `./portscanc ip StartPort EndPort`

 -Scan all the ports:
  `./portscanc ip`

 -Example: 
  `./portscanc 192.168.0.1 0 5000`

## Compatibility:
Tested in Kali GNU/Linux 2023.3 (Debian).
Doest not work in Windows.

