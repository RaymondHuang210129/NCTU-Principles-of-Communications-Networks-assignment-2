# NCTU-Principles-of-Communications-Networks-assignment-2
	Principles of Communications Networks Homework Assignment 2
1. [20%] Please write a channel request generator. The arrival rate of the channel request follows Poisson
distribution with mean 0.5. In addition, please show the inter-arrival time distribution of these channel
requests is Exponential distribution. [Hint: you can plot the pdf of the inter-arrival time]

2. [80%] Considering the cell planning in the figure below. The cluster size is 3 (cells with the same color
are in a cluster); the cell radius and the frequency reuse distance are 100 m and 300 m, respectively. In
addition, each cell is allocated 5 traffic channels, while the channels may be lent to neighboring cells
when needed. We assume that the arrival process and service time of calls in each cells follow the
Poisson distribution and Exponential distribution, respectively. We define lambda = 1 / min and miu = 0.2 / min. As for cell i, the mean arrival rate lambda(i) and mean service rate miu(i) are [(i mod 4) + 1] * lambda and [(i mod 4) + 1] * miu, respectively. The simulation time is 100 min.
(1) Without channel borrowing scheme, what the average blocking probability of the cellular system?
(2) When a cell can borrow channels from its richest neighboring cell (must return the borrowed
channel when one nominal channel becomes free), what the average blocking probability? Whats
the average time consumption to borrow a channel?

                    ______
                   /      \
                  /        \
                 /   BS7    \______
                 \          /      \
                  \        /        \
                   \______/   BS9    \
                   /      \          /
                  /        \        /
	   ______/   BS8    \______/
	  /      \          /      \
	 /        \        /        \
	/   BS1    \______/   BS4    \______
	\          /      \          /      \
	 \        /        \        /        \
	  \______/   BS3    \______/   BS6    \
          /      \          /      \          /
         /        \        /        \        /
        /   BS2    \______/   BS5    \______/
        \          /      \          /
         \        /        \        /
          \______/   BS10   \______/
                 \          /      \
                  \        /        \
                   \______/   BS12   \
                   /      \          /
                  /        \        /
                 /   BS11   \______/
                 \          /
                  \        /
                   \______/
