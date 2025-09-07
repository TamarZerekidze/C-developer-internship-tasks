# C-developer-internship-tasks

You may complete one task in Bash and one of your choice in C.

## Task #1				
Write a bash script that finds all files containing C programming language texts (the names of such files are determined by the *.c mask) in the working directory and its subdirectories and makes a copy of each file, adding the .orig extension to the file name.


**Example**: let the working directory be `/home/some_project`. The structure of the directory and its subdirectories is as follows:


```
/home/some_project 
    Makefile				
    Include
        Common.h
        util.h
    src			
        Main.c
        util.c
```

After the script runs, the directory structure will change to:

```
/home/some_project
    Makefile
    Include
        common.h
        util.h
    src
        main.c
        main.c.orig
        util.c
        util.c.orig
```

_**Additional materials:**_
* [Shell Scripting Tutorial](https://www.tutorialspoint.com/unix/shell_scripting.htm)
* [find(1)](https://man7.org/linux/man-pages/man1/find.1.html) - Linux manual page


## Task #2					
Write in C the simplest analog of the **ls** utility that prints the contents of the working directory and all its subdirectories. 

The program's output should be listings similar to those presented in the first task. To accomplish this, use the following library functions: **opendir()**, **readdir()**, **closedir()**.


## Task #3
Write a program that takes 4 arguments: **prog1**, **prog2**, **prog3**, and **file**, and implements with the standard library and system calls the shell command: 

`prog1 && prog2 | prog3 > file`
