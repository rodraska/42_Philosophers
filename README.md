42_Philosophers is a project developed in C for 42 School.

It is the dining philosophers problem, which is an example problem designed to illustrate synchronization issues and possible solutions to solve them.

One or more philosophers sit at a round table and at the middle of the table there is a bowl of spaghetti. Each philosopher has a fork and they need two forks to eat from the bowl of spaghetti so they cannot eat all at the same time.
They alternatively eat, think and sleep. When a philosopher is able to grab two forks he starts eating for a certain amount of time (time_to_eat). After he has finished eating, he puts both forks back in the table and starts sleeping for a certain amount of time (time_to_sleep). Once they wake up, they start thinking until they are able to start eating again.
If a philosopher is unable to eat for a certain amount of time (time_to_die) the philospher dies and the simulation stops.

The problem consists in designing a concurrent algorithm such that no philosopher will starve and they are all able to alternate turns eating indefinitely.

In this project, each philosopher is a thread and each fork is a mutex.
A multithreaded program contains two or more threads that run concurrently and share rescources, code sections and data sections. Because threads run parallel to each other, it is necessary to ensure that two concurrent threads do not simultaneously execute some particular program section, or access a shared memory block.
To ensure synchronization between threads, we use a mutex which is a lock that is set before accessing a shared resource or memory block and released after using it.

The solution I used to solve this problem is the resource hierarchy solution. It assigns a partial order to the resources (forks), and establishes that all resources will be requested in order and that no two resources unrelated by order will ever be used by a single unit of work (philosopher).
The forks will be numbered from 1 until the number of philosophers and each philosopher will always pick uo the lower-numbered fork first (their own fork) and then the higher-numbered fork (the fork belonging to the philospher to his right), from the forks they plan to use. The initiation of the threads by odd numbered philosopher is delayed by a bit to avoid all philosophers from picking up their own fork at the dame time, leading to a deadlock and ensure the even numbered philosophers grab two forks, wat first and then give their turn tk the odd numbered philosophers.
