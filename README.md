# Philosophers
My solutions to the problem of dining philosophers: while philosophers are threads (philo/ folder) or processes (philo_bonus/).

## Сonditions of the problem (for philo/)
  Conditions for philo/ folder.
- One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

## Сonditions of the problem (for philo_bonus/)
The specific rules for the bonus part are:
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a process. But the main process should not be a
philosopher.

### More conditions, if you want:
[en.subject.pdf](https://github.com/squickfi/philosophers/blob/master/en.subject.pdf)

## Usage
	make
	./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philosopher must eat (optional)]
Time should be in milliseconds.