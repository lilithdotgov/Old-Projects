//Problem 7.1:

/*
Discussion:
First, we need to check for one of two scenarios. Either the customer goes into a queue and waits, or does not and so the time spent
in queue is 0. To check this we can count the number of arrivals and departures that occured before A(i), if there is an equal amount
then that indicates we have 0 people in the system, and so time spent is 0. 

Otherwise, to find the time customer i spends waiting in queue we can subtract the time of departure of the prior customer by the time of arrival.
Or simply: D(i - 1) - A(i) = time spent waiting for customer i.
*/

//Problem 7.2:

/*
Discussion:
We'd want to have a conditional for the situation that could cause idle time, which is the scenario of n = 0 (no customers in system) and so we 
know that we don't need to bother running that check for Case III/IV since if it's past closing time and we have no customers we just end the 
system. Case I is tempting to look into since it does run when n = 0 and with no one in the system t_departure = Inf, so t_arrival < t_departure 
is always True. However, this complicates things when considering the initial case, it's resolvable but annoying. So then what?

Well, Case II DOES run when n = 1 and when their departure is before an arrival, which means it leads to the n = 0 scenario we want. This means we
don't need to check for this case at the top of each loop, only when in Case II. It just so happens that in Case II we already have a check for 
when n = 0, meaning we don't need to add an extra comparison! 

In which case, we would take our variable t_idle and increase it by the time between the last departure (which is the current time), and the
next arrival which we already have calculated. 

EXCEPT! We need to consider two cases: start of the day and the end. At the start of the day n = 0 and we generate t_arrival and set t_departure
to Inf, but the loop causes this state to always go to Case I, and so we never add the wait between start of the day and the first customer. 
So, in initialization we need to set t_idle to t_arrival. 

As for ending, if n = 0 and T_end < t_arrival, we do not want to add the time between last departure and next arrival, instead we need to add 
between last departure and closing time. We can do this by having each t_idle update be an increase by min(T_end - t, t_arrival - t). 
This works, but it's a bit of a waste to do this extra computation when we only care about it for the last case, so let's instead look at 
Case IV, which conveniently already computes the extra time 

So, the change to the algorithm would look like this:

Initialization: t_idle = t_arrival, everything else leave the same

Case II,:
->leave the same (so t = t_departure, giving us our last departure time)
->If n = 0:
-->t_departure = Inf (same as before)
-->t_idle = t_idle + min(T_end - t, t_arrival - t)
->D(N_d) = t (same as before)

With this, at the end we will have our t_idle = time spent idle!
*/
