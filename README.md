# Text Frequency Analyzer and Bar Chart Generator

A C++ word frequency counter and bar chart generator built with a custom
templated linked list. Built for CMSC 202 (Computer Science II) at UMBC.

## What it does

Reads any text file, counts how often each item appears, optionally filters
results, sorts by frequency, and displays a visual bar chart. Exports results
to a file. The core data structure is a custom templated linked list — not STL
containers — demonstrating the Rule of Three and generic programming.

## Features

- Load and parse any text file word by word
- Convert all input to lowercase and strip punctuation
- Optionally remove common words (the, and, is, etc.) using a built-in exclusion list
- Optionally remove words appearing only once
- Sort results by frequency using STL multimap
- Display bar chart from highest to lowest frequency
- Export bar chart to a user-specified output file

## Example

Input: 
dog cat dog dog bird cat

Output:
        dog:***
        cat:**
       bird:*

## Templated Design

The project is built around a custom `LL<T>` templated linked list where each
node stores a `pair<T, int>` — the item and its frequency count. Because it is
templated, it works with strings, integers, floats, or any comparable type as
demonstrated by the included test files.

## Rule of Three

The `LL` class fully implements:
- **Destructor** — deallocates all dynamically allocated nodes
- **Copy Constructor** — creates a deep copy of an existing list
- **Assignment Operator** — makes two lists identical

These are required for correct memory management in C++ and are common topics
in technical interviews.

## Project Structure

| File | Description |
|---|---|
| `LL.cpp` | Templated linked list implementation |
| `Bar.h` / `Bar.cpp` | Bar chart and frequency analysis logic |
| `proj5.cpp` | Entry point |
| `LL_test.cpp` | Standalone test for LL class |
| `proj5_test1.txt` | Essay text input |
| `proj5_test2.txt` | Additional text input |
| `proj5_test3.txt` | Integer input |
| `proj5_test4.txt` | Float input |
| `proj5_test5.txt` | DNA sequence input |

## How to Build and Run

```bash
# Build main program
make proj5

# Run with different test files
make run1    # Essay text
make run2    # Additional text
make run3    # Integer data
make run4    # Float data
make run5    # DNA sequence data

# Build and test LL class separately
make LL_test
./LL_test

# Check for memory leaks
make val1
make valLL
```

## Technical Concepts

- Templates and generic programming
- Custom linked lists
- Rule of Three
- Dynamic memory management
- File I/O and string processing
- Frequency analysis
- STL multimap for sorting
- Operator overloading
- Data visualization

## Course

CMSC 202 — Computer Science II, University of Maryland Baltimore County (UMBC)