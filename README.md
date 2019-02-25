# Load Balancing Program

Program to simulate how long it takes for activity to converge to a balanced workload among processors

### Constraints

What things you need to install the software and how to install them

```
* A distributed computing system with k physical processors connected on a ring network

* Each processor P(i) connects to two neighbors P(i+1)mod(k) and P(i+1)mod(k).

* Each procesor P(i) is loaded with a set number of load units.

* Time is divided into unit intervals.

* Each processor schedules load balancing activity at random time intervals.

* Each processor whose load balancing activity is current will look at its two neighbors,
  compute an average number of load units each should have to equalize each other's
  load and will "give" load units to the neighboring processor(s) such that the dierence
  in load units between neighboring processors is balanced. If by "giving" load units
  balancing is not possible, the processor does nothing.

```