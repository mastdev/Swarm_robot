The project contains arduino code for swarm robot that involve use of two bot that wirelessly communicate .
One of the bot follows white line while other copies the the one following line

We used
4 DC motors
2 L298n Motor Drives
A pair of Rf transmitter and reciever 433 Mhz
2 Arduino Mega and Jumper Wires

We used PID Code on the master bot following the white line and then replicated it to the slave bot.
We transmitted integer values or the correction to the slave bot.
We used the help of Radiohead Serial Library for communication between transmitter and reciever.