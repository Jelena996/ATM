# ATM

An ATM machine is a class witch has an ID, a name and location and it functions like a state machine. 
It functions like a graph of machine states. The ATM machine has an information of its current state. 
When the machine changes  a state the next state is always a clone of the requested next state. 


A credit card is a class whitch has an id, a clinet name and a number (available assets). 
The number (assets) can be decreased and increased.

State is a class whitch is used to go through different states of the atm machine workflow
(Enter,Exit,Menu,Choose a Service,Service1,Service2 etc,print report).

A session is a class whitch has an ID,time of start, and end of user session, it begins when the user switches from a entry state
to another state and ends when the user returns to the entry state, the ATM machine stores information of all states.
A session contains a sequence of states, through which the ATM went during the session. It prints the session on an output file after 
completion.
