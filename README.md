42 Project : philosophers
<a name="readme-top"></a>
<div align="center">

# philosophers

> Who thought threading on parallelism & concurrency land could be so philosophically deadly 🕱

<p>
    <img src="https://img.shields.io/badge/score-%20%2F%20100-success?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/PedroZappa/42_push_swap?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/PedroZappa/42_push_swap?style=for-the-badge&logo=" />
    <img src="https://img.shields.io/github/languages/top/PedroZappa/42_push_swap?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/PedroZappa/42_push_swap?style=for-the-badge" />
</p>

___

<!-- <img alt="philosophers demo" src="./video/philosophers-demo.gif" width="100%" /> -->

___

<h3>Table o'Contents</h3>

</div>

<!-- mtoc-start -->

* [About 📌](#about-)
* [`philosophers` Problem 🜎](#philosophers-problem-)
* [`philosophers` Requirements Overview ✅](#philosophers-requirements-overview-)
* [`philosophers`  Mandatory Implementation 📜](#philosophers--mandatory-implementation-)
* [Usage 🏁](#usage-)
* [Tests 🧪](#tests-)
* [References 📚](#references-)
* [License 📖](#license-)

<!-- mtoc-end -->

# About 📌

This is a classic CS project conceived as an introduction to the basics of threading a process. It gives an introductory glance into the difficulties contingent to the non-deterministic nature of multi-threaded application programming.

## `philosophers` Problem 🜎

*  **One or more philosophers** sit at a round table.
There is a large bowl of spaghetti in the middle of the table.

* The philosophers alternate between eating, thinking, or sleeping:
	- While they are eating, they are not thinking nor sleeping;
	- while thinking, they are not eating nor sleeping;
	- While sleeping, they are not eating nor thinking.
* There are also **forks** on the table. There are **as many forks as philosophers**.
* A philosopher **must take two forks to eat**, one in each hand.
* When finished eating, they **put their forks back on the table** and start sleeping. 
* Once awake, they start thinking again. 
* The simulation **stops** when a philosopher **dies of starvation**.
* Every philosopher needs to eat and should never starve.
* Philosophers don’t speak with each other.
* Philosophers don’t know if another philosopher is about to die.

## `philosophers` Requirements Overview ✅

- The program must not include any global variables.

- It should accept the following command line arguments (as positive integers):
```sh
./philosophers <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_meals]
```

- `n_philos` also the number of forks.

- `time_to_die` the time to die in milliseconds (length of philo's life).

- `time_to_eat` the time to eat in milliseconds (length of time to hold forks).

- `time_to_sleep` the time to sleep in milliseconds (length of time to rest).

- `max_meals` the maximum number of meals for the simulation (optional argument).

- Each philosopher is numbered from 1 to `n_philos`.

- Philosophers number 1 should be sitting next to philosopher `n_philos` and philosophers number 2.

Regarding logs, the program should report any state change of a philosopher formatted as:

- `timestamp_in_ms <philo_n> has taken a fork.`
- `timestamp_in_ms <philo_n> is eating.`
- `timestamp_in_ms <philo_n> is sleeping.`
- `timestamp_in_ms <philo_n> is thinking.`
- `timestamp_in_ms <philo_n> has died.`

- Messages should not mix with each other.

- A message announcing the end of the simulation should be displayed no more than 10ms after the time of death of the philosopher.

___
# `philosophers`  Mandatory Implementation 📜

___

# Usage 🏁

___

# Tests 🧪

___

# References 📚

___

# License 📖

This work is published under the terms of <a href="https://github.com/PedroZappa/42_philosophers/blob/main/LICENSE">42 Unlicense</a>.

<p align="right">(<a href="#readme-top">get to top</a>)</p>
