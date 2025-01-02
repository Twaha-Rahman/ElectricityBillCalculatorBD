# Electricity Bill Calculator BD

The **Electricity Bill Calculator** project is C++ project aimed at automating
the process of calculating electricity bills based on Bangladesh's
[electricity unit price](https://bpdb.portal.gov.bd/sites/default/files/files/bpdb.portal.gov.bd/page/4a0f045a_1415_45f1_9e7c_02a8ed4f103c/2024-03-01-13-45-740f1fb3c50588f18077bdce93250b9a.pdf).

# Motivation

Electricity billing is a common and essential utility for households,
businesses, and industries. However, manual calculations can be time-consuming
and prone to errors. This project addresses these challenges by providing an
automated, accurate, and user-friendly solution. The project is designed to
simulate a real-world billing system by utilizing core OOP concepts such as
encapsulation, inheritance, and polymorphism. It allows users to input essential
details, such as device usage time (hours), and the user can customize their own
device then calculates the total bill per day and per month based on
[Bangladesh electricity unit price](https://bpdb.portal.gov.bd/sites/default/files/files/bpdb.portal.gov.bd/page/4a0f045a_1415_45f1_9e7c_02a8ed4f103c/2024-03-01-13-45-740f1fb3c50588f18077bdce93250b9a.pdf).

# Compilation

If you have [GNU `make`](https://www.gnu.org/software/make/) installed, building
the project and running it is as simple as running:

```shell
make run
```

If you don't have [GNU `make`](https://www.gnu.org/software/make/), then just
use a C++ compiler to compile all the C++ source files.

If you're using `g++`, you'd need to run the following command to compile the
project:

```sh
g++ *.cpp devices/*.cpp -o app
```

Then, to run the built binary in Unix based operating systems run the following:

```shell
./a.out
```

To run the built binary in Windows, run the following:

```shell
.\a.exe
```

This example assumes you're running it on Unix based OSs. Instructions for
Windows should be similar, but may require slight modification.

# Contributing

Feel free to contribute to the project if you want to. Just fork it, create a
branch, make your changes, and create a pull request.
