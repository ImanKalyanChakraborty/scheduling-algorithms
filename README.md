# CPU Scheduling Algorithm implementation in C++

The above code is an implementation of 3 specific CPU scheduling algorithms in C++, namely,

1. **First Come First Serve** : In First Come First Serve Algorithm, we allow the process to execute in linear manner This means that whichever process enters process enters the ready queue first is executed first. (Source : https://www.javatpoint.com/os-fcfs-scheduling)

2. **Round Robin Scheduling**: Round Robin CPU Scheduling uses Time Quantum (TQ). The Time Quantum is something which is removed from the Burst Time and lets the chunk of process to be completed. Time Sharing is the main emphasis of the algorithm. Each step of this algorithm is carried out cyclically. The system defines a specific time slice, known as a time quantum. Time Sharing is the main emphasis of the algorithm. Each step of this algorithm is carried out cyclically. The system defines a specific time slice, known as a time quantum. First, the processes which are eligible to enter the ready queue enter the ready queue. After entering the first process in Ready Queue is executed for a Time Quantum chunk of time. After execution is complete, the process is removed from the ready queue. Even now the process requires some time to complete its execution, then the process is added to Ready Queue. The Ready Queue does not hold processes which already present in the Ready Queue. The Ready Queue is designed in such a manner that it does not hold non unique processes. By holding same processes Redundancy of the processes increases. After, the process execution is complete, the Ready Queue does not take the completed process for holding. (Source : https://www.javatpoint.com/os-round-robin-scheduling-algorithm)

3. **Shortest Remaining Time First** : In SRTF, the execution of the process can be stopped after certain amount of time. At the arrival of every process, the short term scheduler schedules the process with the least remaining burst time among the list of available processes and the running process. (Source : https://www.javatpoint.com/os-srtf-scheduling-algorithm)

# Running the code

The steps for running the code are quite simple. After opening the main.cpp file, go to the main method. From there, you need to push the processes with their arrival time and CPU burst time into the processes vector. The processes should be pushed in the form of tuples containing name of process, arrival time and CPU burst time, as shown in the main.cpp file. After saving main.cpp file, the following lines of code need to be run from the terminal:

```
g++ main.cpp -std=c++11
```
```
./a.out
```

The output will show the average turnaround time for the processes along with a full timeline as to when which process is running.

# Links
Below you can find my Twitter and LinkedIn Pages. Feel free to connect 😊. Thank you for reading through this Project.

    LinkedIn - https://www.linkedin.com/in/imankalyanchakraborty/
    Twitter - https://twitter.com/ikc1975
