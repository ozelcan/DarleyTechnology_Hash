# Fixed-Size Hash Table with Linear Probing in C++

## 🚀 Design Overview

### Step-by-Step Summary

- **Parsing Input Dataset**  
  Words were read from a file (`unique_words.csv`) with one word per line. These were cleaned and inserted into the hash table with an incrementing integer value as the associated value.

- **Fixed-Size Hash Table**  
  Implemented using `std::array` with a table size of **32,753**, a large prime number chosen to reduce hash collisions and support efficient probing.

- **Hash Function**  
  A **polynomial rolling hash** was used for string keys to ensure uniform distribution across the hash table.

- **Collision Handling**  
  **Linear probing** was used to resolve collisions. To keep operations `O(1)` in practice, we maintained a low load factor and tracked probe depth for performance insights.

- **Order Tracking**  
  Two additional arrays were used:
  - `order[]`: Tracks insertion/update order of entries.
  - `order_index[]`: Maps a table index to its position in the order array for constant-time updates.

- **Removal & Reordering**  
  Deleted entries were cleared by resetting the `Entry{}` at that index. The order arrays were updated using a **swap-remove** technique for `O(1)` deletions and reordering.

- **Auxiliary Info**  
  During insertion, we tracked the **maximum probe count** needed to locate an empty slot — this provides practical insight into hash distribution efficiency.

---

## 📊 Performance & Results

- **Number of inserted words**: ~10,974  
- **Table size**: 32,753  
- **Load factor**: ~33% (ensures minimal clustering)  
- **Maximum probe count during insertions**: 17  

---

## ⚙️ Build Instructions

### 🧪 Build from Terminal

Make sure the following files are in your project:
   - `main.cpp`
   - `HashTable.cpp`
   - `HashTable.h`
   - `unique_words.csv`
     
You can compile manually using `g++`:

```bash
g++ -std=c++17 -g main.cpp HashTable.cpp -o main
./main
