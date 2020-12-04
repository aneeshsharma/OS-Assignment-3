# OS-Assignment-3

The assignment contains 3 questions. The questions are under the directories -
- `Q1/`
- `Q2/`
- `Q3/`

## Question 1

There are 3 programs -
- `CI.c` - representing Course Instructor
- `TA.c` - representing Teaching Assistant
- `Student.c` - representing the students

Build the programs using the command - `make`.
This should output 3 executables, namely - `CI.o`, `TA.o` and `Student.o`. Run the three processes as -
```
$ ./CI.o
```
```
$ ./TA.o
```
```
$ ./Student.o <student id>
```

The student id in the `Student.o` program needs to be within the range 1-5 and is provided as a command line argument.

Once the processes are running, provide the marks as input to `CI.o`. The data flow should occur and TA should calculate grades and send back to the CI. The CI then sends the marks to the respective students. The students read the marks from the respective queue and prints the marks.

## Question 2
This consists of a single program - `Q2.c`. Build this program using -
```
$ gcc Q2.c -o Q2.o
```
This should output an executable - `Q2.o`. Run the program as -
```
$ ./Q2.o
```

The format is as follows: 
- Processes No within `0` - `n-1`
- Resource No from `0` - `m-1`

The arrays denote the following -
- `alloc` - resource allocated to the process
- `need` - resource required for the process
- `max` - maximum resource count the process can request
- `complete` - temporary flag when an array finishes the process

Each row indicates a process.
Each column indicates a resource.

## Question 3
This consists of a single program - `Q3.c`. Build the program using -
```
$ gcc Q3.c -o Q3.o -lpthread
```

This should output an executable - `Q2.o`. Run the program as -
```
$ ./Q3.o
```

This program simulates the Dining Philosopher Problem which states that - K philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pickup the two chopsticks adjacent to him. One chopstick may be picked up by any one of its adjacent followers but not both.

The philosopher has 3 states -
- Thinking 
- Hungry
- Eating
