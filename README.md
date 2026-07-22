# STL Container Benchmarks

## Project Overview

This project compares the lookup performance of two C++ STL associative containers: `std::map` and `std::unordered_map`. The benchmark uses data parsed from a CSV file and measures lookup performance using `std::chrono`.

## Benchmarking Approach

- Parsed 848 records from a CSV file.
- Stored the records in both `std::map` and `std::unordered_map`.
- Generated 100,000 random lookup keys.
- Measured lookup times using `std::chrono::high_resolution_clock`.
- Compared the execution times of both containers.

## std::map

- Implemented as a Red-Black Tree.
- Stores elements in sorted order.
- Average lookup complexity: **O(log n)**.

### Advantages

- Maintains sorted order.
- Supports ordered traversal.
- Predictable logarithmic performance.

### Disadvantages

- Slower lookups than hash tables.
- Higher tree traversal overhead.

## std::unordered_map

- Implemented as a Hash Table.
- Stores elements without any ordering.
- Average lookup complexity: **O(1)**.

### Advantages

- Extremely fast average lookups.
- Excellent for key-based searching.

### Disadvantages

- No ordering of elements.
- Worst-case lookup can degrade to O(n).

## Benchmark Results

| Container | Lookup Time |
|------------|------------:|
| std::map | 51266 µs |
| std::unordered_map | 12849 µs |

The benchmark showed that `std::unordered_map` performed approximately **4× faster** than `std::map` for repeated lookup operations due to its hash table implementation.