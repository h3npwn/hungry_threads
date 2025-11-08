# 🧠 Philosophers

`philosophers` is a multithreading program written in C that simulates the **Dining Philosophers Problem**, a classic example in computer science used to illustrate problems of **concurrency**, **synchronization**, and **resource sharing**.

---

## 🚀 Overview

The goal of `philosophers` is to understand how multiple threads (representing philosophers) can work in parallel while accessing shared resources (forks) without causing **deadlocks** or **race conditions**.

Each philosopher alternates between **thinking**, **eating**, and **sleeping**.  
To eat, a philosopher must take both forks — one from the left and one from the right. Proper synchronization ensures that all philosophers get a chance to eat without conflict.

---

## ⚙️ Rules

- There are **N philosophers** sitting around a circular table.  
- Each philosopher has a **fork on their left** and **right**.  
- A philosopher can only eat when **both forks** are available.  
- After eating, they put down their forks and start sleeping, then thinking again.  
- If a philosopher doesn’t eat within a certain time (`time_to_die`), they die.

---

## 🧠 Parameters

Your program takes the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
