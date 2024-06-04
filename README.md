# CheckIT: Plagiarism and Similarity Detector

## Description
CheckIT is a simple plagiarism and similarity detector that uses Brute Force and Rabin-Karp algorithms. The detector also employs the sliding window technique to provide more accurate substring matches.

## Features
- **Brute Force Algorithm**: Compares each substring to identify similarities.
- **Rabin-Karp Algorithm**: Utilizes hash functions for efficient substring search.
- **Sliding Window Technique**: Enhances accuracy by considering overlapping substrings.

## File Structure
- **BruteForce**: Contains the implementation of the Brute Force algorithm.
- **RabinKarp**: Contains the implementation of the Rabin-Karp algorithm.
- **CorpusTexts**: Sample texts used for testing and demonstration.

## Getting Started

### Prerequisites
- C++ compiler

### Installation
Clone the repository:
```sh
git clone https://github.com/Ahmed-Fawzy14/CheckIT.git
```
### Installation
cd CheckIT
g++ -o checkit main.cpp
./checkit

###Contributions
