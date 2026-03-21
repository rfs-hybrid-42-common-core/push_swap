*This project has been created as part of the 42 curriculum by maaugust.*

<div align="center">
  <img src="https://raw.githubusercontent.com/rfs-hybrid/42-Common-Core/main/assets/covers/cover-push_swap-bonus.png" alt="Push_swap Cover" width="100%" />
</div>

<div align="center">
  <h1>🔄 Push_swap: Because Swap_push doesn't feel as natural</h1>
  <img src="https://img.shields.io/badge/Language-C-blue" />
  <img src="https://img.shields.io/badge/Grade-125%2F100-success" />
  <img src="https://img.shields.io/badge/Norminette-Passing-success" />
</div>

---

## 💡 Description
**Push_swap** is an algorithmic project in the 42 curriculum that challenges you to sort data in a stack using a highly limited set of instructions, aiming to achieve the lowest possible number of actions. 

The primary goal of this project is to introduce the concept of algorithmic complexity ($Big\ O$ notation) and benchmarking. You are given two stacks (`a` and `b`). Stack `a` contains a random sequence of unique integers, while stack `b` is empty. By utilizing only specific `push`, `swap`, and `rotate` operations, you must calculate and display the shortest possible sequence of instructions needed to completely sort stack `a`.

This implementation comfortably crushes the maximum evaluation benchmarks (sorting 100 numbers in < 700 operations, and 500 numbers in < 5500 operations).

---

## 📑 Features

### 🔹 Mandatory Part: The Sorter
Parses the input, completely validates it (checking for duplicates, integer limits, and non-numeric characters), and outputs the exact sequence of stack operations to `stdout`.
* **Operations Used:** `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.

### 🚀 Bonus Part: The Checker
A standalone program (`checker`) that takes the same integer arguments, reads a list of generated instructions from standard input (`stdin`) using a custom `get_next_line`, and silently applies them to the stack. 
* Outputs `OK\n` if stack `a` is properly sorted and `b` is empty.
* Outputs `KO\n` if the sorting failed.
* Completely reuses the core execution and parsing logic from the mandatory part by utilizing a `check` boolean flag to silence the standard output.

---

## 🧠 Algorithm & Data Structure

### Data Structure: Circular Doubly Linked List
To seamlessly execute `rotate` (shifting up) and `reverse_rotate` (shifting down) operations without traversing the entire list every time, the stacks are implemented as **circular doubly linked lists**. The `next` pointer of the last node connects back to the head, and the `prev` pointer of the head connects to the tail, making boundary operations instantaneous $O(1)$.

### Algorithm: LIS + The Turk Algorithm
Standard sorting algorithms (like Quick Sort or Merge Sort) don't map well to the restricted stack operations. Instead, this project uses a multi-phase, highly optimized mechanical sorting approach:

1. **Longest Increasing Subsequence (LIS):** Using Dynamic Programming, the algorithm calculates the longest naturally ascending sequence of numbers already present in stack `a`. These "LIS" numbers are flagged and kept in stack `a`, serving as a sorted anchor.
2. **Push to B:** Everything *not* in the LIS is pushed to stack `b`. This instantly leaves stack `a` perfectly sorted (though dispersed).
3. **The Turk Algorithm (Cost Calculation):**
   For every node in stack `b`, the algorithm calculates the exact "cost" (number of operations) to move it to the top of `b` *and* simultaneously rotate its correct target position to the top of `a`. It leverages synchronized rotations (`rr`, `rrr`) to minimize cost.
4. **Execution:** The absolute cheapest node in `b` is executed and pushed back to `a`. This loops until `b` is empty.
5. **Final Alignment:** Stack `a` is rotated until the absolute minimum value sits at the top.

---

## 🛠️ Instructions

### 📦 Compilation
This project includes a comprehensive `Makefile` to handle compilation and library dependencies.

**Compile the mandatory `push_swap` program:**
```bash
make
```

**Compile the bonus `checker` program:**
```bash
make bonus
```

### 🧹 Cleaning
* `make clean`: Removes object files (`.o`).
* `make fclean`: Removes object files, the executables, and cleans the embedded `libft`.
* `make re`: Performs a clean re-build.

### 💻 Usage

**Running Push_swap:**
Pass a list of integers as arguments. It handles both multiple arguments and a single formatted string.
```bash
./push_swap 4 67 3 87 23
```
*Output:*
```text
pb
pb
ra
pa
pa
```

**Running the Checker:**
You can pipe the output of `push_swap` directly into the `checker` to verify the algorithm's success:
```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```
*Expected Output:*
```text
OK
```

**Testing Operation Counts:**
To see exactly how many operations your algorithm used for a random set:
```bash
ARG=$(seq -1000 1000 | shuf -n 500); ./push_swap $ARG | wc -l
```

### 🧪 Testing & Visualization
To ensure your algorithm is fully optimized and memory leak-free, it is highly recommended to use third-party testers and visualizers before your evaluation.

<div align="center">
  <img src="https://raw.githubusercontent.com/rfs-hybrid-42-common-core/push_swap/main/assets/gif/push_swap_visualizer.gif" alt="Push Swap Visualizer 500 numbers" />
  <p><i>Example of a 500-number sort using a graphical visualizer.</i></p>
</div>

**Recommended Testers & Visualizers:**
* **[Push-Swap-Tester by gemartin99](https://github.com/gemartin99/Push-Swap-Tester):** A fantastic bash script that runs hundreds of automated iterations to calculate your average operation count and catch edge-case infinite loops.
* **[Push_swap Visualizer by o-reo](https://github.com/o-reo/push_swap_visualizer):** The classic, highly popular C++ graphical visualizer (showcased in the GIF above) that lets you watch your stacks get sorted in real-time.
  * 🔧 *Troubleshooting Note:* If you encounter a `decltype(&pclose)` compilation error on newer Linux systems when building this visualizer, open `src/pushswap.cpp`, go to line 17, and change `decltype(&pclose)` to `int (*)(FILE*)` to bypass the strict compiler warning.
* **[Push_swap Web Visualizer](https://push-swap42-visualizer.vercel.app/):** An excellent web-based manual visualizer. It allows you to step through your operations one by one and see exactly how your algorithm manipulates the stacks in real-time.
* **[Random Number Generator](https://www.calculatorsoup.com/calculators/statistics/random-number-generator.php):** A handy web tool by CalculatorSoup to quickly generate a unique set of random integers for manual testing without relying on terminal commands.

### 🚨 The Norm
Moulinette relies on a program called `norminette` to check if your files comply with the 42 Norm. Every single `.c` and `.h` file must pass this check. If there is a norm error, you will receive a 0.

**The 42 Header:**
Before writing any code, every file must start with the standard 42 header. `norminette` will automatically fail any file missing this specific signature.
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:40:15 by maaugust          #+#    #+#             */
/*   Updated: 2025/06/26 15:46:43 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
```

Run the following command in the root of your repository to check all your files at once:
```bash
norminette -R CheckForbiddenSourceHeader srcs/ bonus/ includes/
```

---

## 📚 Resources & References
* [Longest Increasing Subsequence (GeeksforGeeks)](https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)
* [The Turk Algorithm (Medium)](https://medium.com/@ali.boca.ali/push-swap-the-awesome-algorithm-92fee1412563)
* [42 Norm V4](https://cdn.intra.42.fr/pdf/pdf/96987/en.norm.pdf) - The strict coding standard for 42 C projects.
* [Official 42 Norminette Repository](https://github.com/42School/norminette) - The open-source linter enforcing the strict 42 coding standard.

### 🤖 AI Usage Guidelines
*Per the subject requirements:*
* **Tasks:** AI tools were used exclusively for generating portfolio-ready Doxygen comments, structuring the README template, and discussing the architectural trade-offs of Big O time vs. space complexity during the parsing phase.
* **Code:** No AI-generated code was used to solve the algorithm. All linked list manipulations, LIS dynamic programming matrices, and operation cost calculations were completely manually coded to ensure a fundamental, defendable understanding of algorithmic logic.
