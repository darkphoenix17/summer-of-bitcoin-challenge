# Summer of Bitcoin Challenge

This repository contains solution to the [Summer of Bitcoin Challenge](https://summerofbitcoin.org/)

## How to run code

<hr>

As solution is in C++, it requires [GNU Compiler](https://gcc.gnu.org/) <br>
Get to the home directory of the repository

For Linux, run

```sh
g++ solution.cpp
./a.out
```

For Windows, run

```sh
g++ solution.cpp
./a.exe
```

<hr>

## Basic Approach

> The basic logic is to check for fee/weight ratio and select those transactions whose value is high as that will maximize the total earning of the miner.
> The approach also validate transaction by not considering those transaction which have **uncomfirmed parent transaction**.

<hr>

![Summer of Bitcoin Logo](https://summerofbitcoin.org/img/summerbig1.png)
