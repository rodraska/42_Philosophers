42_Philosophers is a project developed in C for 42 School.

It is the dining philosophers problem, which is an example problem designed to illustrate synchronization issues and possible solutions to solve them.

One or more philosophers sit at a round table and at the middle of the table there is a bowl of spaghetti. Each philosopher has a fork and they need two forks to eat from the bowl of spaghetti so they cannot eat all at the same time.
They alternatively eat, think and sleep. When a philosopher is able to grab two forks he starts eating for a certain amount of time (time_to_eat). After he has finished eating, he puts both forks back in the table and starts sleeping for a certain amount of time (time_to_sleep). Once they wake up, they start thinking until they are able to start eating again.
If a philosopher is unable to eat for a certain amount of time (time_to_die) the philospher dies and the simulation stops.
