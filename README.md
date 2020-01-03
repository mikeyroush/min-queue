# min-queue

This project implements a min-queue data structure. A FIFO queue that allows for O(1) enqueue(), dequeue(), and min().  This is different from a priority queue because in this implementation min() simply returns the minimum value without removing it.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for testing purposes.

### Prerequisites

A working command line

### Installing and Running

Download the zip then link the files in the command line via the makefile and run the executable

Navigate to the correct directory and utilize the makefile

```console
foo@bar:~$ cd /path/to/directory/here
foo@bar:~$ make all
```

This will have created a few .o files and an executable. To run it, do as follows...

```console
foo@bar:~$ ./Main
```

Demo

```console
Create a new queue
isEmpty: 1
queue:

Enqueue 10 nodes with values 10,20...100
queue: 10 20 30 40 50 60 70 80 90 100

Dequeue 1st node
dequeued value: 10
queue: 20 30 40 50 60 70 80 90 100

Enque a value of 1 and return min value and size of queue
queue: 20 30 40 50 60 70 80 90 100 1

min: 1
size: 10
```

## Authors

* **Michael Roush** - *Project completion*

## License

Copyright © 2017 Michael Roush. All rights reserved.

