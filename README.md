**Note** : If you found this repo you should stop for a second and [read this](https://atomys.me/en/s42-sunset-story/)

42 Project : philosophers
<a name="readme-top"></a>
<div align="center">

# philosophers

> Who thought treading on parallelism & concurrency land could be so philosophically deadly 🕱

<p>
    <img src="https://img.shields.io/badge/score-%20%2F%20100-success?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/PedroZappa/42_philosophers?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/PedroZappa/42_philosophers?style=for-the-badge&logo=" />
    <img src="https://img.shields.io/github/languages/top/PedroZappa/42_philosophers?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/PedroZappa/42_philosophers?style=for-the-badge" />
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
* [`philosophers`  Bonus Implementation 📜](#philosophers--bonus-implementation-)
* [Usage 🏁](#usage-)
* [Tests & Debug 🧪](#tests--debug-)
* [References 📚](#references-)
* [Documentation](#documentation)
* [Research Papers](#research-papers)
* [Tools](#tools)
* [Articles](#articles)
* [License 📖](#license-)

<!-- mtoc-end -->

# About 📌

This is a classic CS exercise conceived as an introduction to the basics of **threading** a process. It gives an introductory glance into the difficulties contingent to the non-deterministic nature of multi-threaded applications.

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
./philo <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_meals]
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

- Each philosopher should be represented by a thread.

- There is a fork between each pair of philosophers.

- If there is only one philosopher, there should be only one fork on the table.

- Each forks must be pretended by a mutex.


___
# `philosophers`  Bonus Implementation 📜

- All forks are placed in the middle of the table.

- They have no states in memory. The number of available forks is represented by a semaphore.

- Each philosopher should be represented by a process, but the main process should not be a philosopher

> [!Important]
> The code for both implementations is documented with doxygen comments. Enjoy!

___

# Usage 🏁

Clone the repository and cd into either the mandatory (`philo`) or bonus implementation (`philo_bonus`):
```sh
git clone https://github.com/PedroZappa/42_philosophers.git 42_philosophers_passunca
# For the mandatory (Threads implementation w/ mutexes)
cd 42_philosophers_passunca/philo
# For the bonus (Processes implementation w/ semaphores)
cd 42_philosophers_passunca/philo_bonus
```

Build the program:
```sh
# For the mandatory
make
```

Run the program:
```sh
./philo 5 800 200 200
# or with a set max number of meals
./philo 5 800 200 200 7
```

> [!Note]
> To execute the bonus implementation, you will need to instead call `./philo_bonus` command.
___

# Tests & Debug 🧪

Run the following command and look at the `Test Rules 🧪` & `Debug Rules ` to get a comprehensive list of all available test/debug commands:
```sh
make help
```

> [!Note]
> If you use `tmux` you are in for treat 😏
___
# References 📚

## Documentation

- [GDB | Documentation](https://sourceware.org/gdb/current/onlinedocs/gdb)
- [ThreadSanitizerCppManual · google/sanitizers Wiki · GitHub](https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual)
- [Helgrind: a thread error detector | Documentation](https://valgrind.org/docs/manual/hg-manual.html)
- [Instrumentation Options (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html)

## Research Papers

- [Pthreads and OpenMP](https://www.diva-portal.org/smash/get/diva2:944063/FULLTEXT02.pdf)
- [Heuristics for Efficient Dynamic Verification of Message Passing Interface And Thread Programs](https://core.ac.uk/download/pdf/276266676.pdf)
- [Pthreads for Dynamic and Irregular Parallelism](https://core.ac.uk/download/pdf/276266676.pdf)
___
## Tools

- [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/)
- [GitHub - SimonCROS/philosophers-visualizer CLI](https://github.com/SimonCROS/philosophers-visualizer)
- [GitHub - mpdn/unthread: A deterministic, fuzzable pthread implementation](https://github.com/mpdn/unthread)
- [rr: lightweight recording & deterministic debugging](https://rr-project.org/)
	- [Introducing rr Chaos Mode](https://robert.ocallahan.org/2016/02/introducing-rr-chaos-mode.html)

## Articles

- [Philosophers 42 Guide— “The Dining Philosophers Problem” | by Dean Ruina | Medium](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
- [The dining philoshophers (an introduction to multitasking) a 42 The Network project | by MannBell | Medium](https://m4nnb3ll.medium.com/the-dining-philoshophers-an-introduction-to-multitasking-a-42-the-network-project-34e4141dbc49)
___

# License 📖

This work is published under the terms of <a href="https://github.com/PedroZappa/42_philosophers/blob/main/LICENSE">42 Unlicense</a>.

<p align="right">(<a href="#readme-top">get to top</a>)</p>
