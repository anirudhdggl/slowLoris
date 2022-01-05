# slowLoris

Slow Loris is a type of DDoS attack. Before trying it I would love you to know more about it. 
https://en.wikipedia.org/wiki/Slowloris_(computer_security)

# Basic underlying algorithm

This code basically gets the user to enter the target host, the portnumber and number of threads.
It will then initialize n thread and each of the thread would then send a garbage request to the server and keep it busy. As an ideal value enter 1000 threads.

Also, I am using a windows machine so most of the code uses <winsock2.h>. Check for your alternatives for linux or any other OS that you are using.
