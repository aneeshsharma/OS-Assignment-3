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

