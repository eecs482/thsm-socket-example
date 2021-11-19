# Socket Example
Write a simple client and server, where the client sends a string to the server,
the server outputs the string using cout, and then sends some acknowledgement
response back to the client.

## Start
```sh
$ git clone https://github.com/eecs482/thsm-socket-example.git
$ cd thsm-socket-example
$ make
$ ./server &
$ ./client
```

## Bonus
Run your client and server on a CAEN machine (the client and server programs
need to run on the same CAEN machine, since the CAEN firewall won't let you
communicate between machines). Then try communicating with another student in
your section. 