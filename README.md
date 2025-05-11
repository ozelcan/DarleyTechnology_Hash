Design Overview

Step-by-Step Summary

Parsing Input Dataset: Words were read from a file (unique_words.csv) with one word per line. These were cleaned and inserted into the hash table with an incrementing integer value.

Fixed-Size Hash Table: Implemented using std::array with a table size of 32,753, a prime number chosen to reduce collisions.

Hash Function: A polynomial rolling hash was used for string keys to ensure uniform distribution across the table.

Collision Handling: Linear probing was used to resolve collisions. To keep operations O(1) in practice, we track probe depth and designed for low load factor.

Order Tracking: Two arrays were used:

order: keeps track of the insertion/update order of occupied slots.

order_index: maps from a table index to its position in the order array.

Removal & Reordering: Removed entries reset the slot to an empty Entry{} and updated the order arrays using swap-remove in O(1) time.

Auxiliary Info: We tracked the maximum number of probes required during insertion to assess performance.

Performance & Results

Number of inserted words: ~10,974

Table size: 32,753

Load factor: ~33% (ensures low clustering)

Maximum probe count: 17
