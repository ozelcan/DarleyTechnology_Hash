// HashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <array>
#include <optional>
#include <string>

const int TABLE_SIZE = 32753;

struct Entry {
  std::string key;
  int value = 0;
  int timestamp = -1;
};

class HashTable {
public:
  HashTable();

  void insert(const std::string &key, int value);
  void remove(const std::string &key);
  std::optional<int> get(const std::string &key) const;
  std::optional<std::pair<std::string, int>> get_first() const;
  std::optional<std::pair<std::string, int>> get_last() const;
  int get_max_probe() const;

private:
  std::array<Entry, TABLE_SIZE> table;
  std::array<int, TABLE_SIZE> order; // Store indices in insertion/update order
  std::array<int, TABLE_SIZE>
      order_index; // Maps table index to position in order[]
  int current_time;
  int order_count;
  mutable int max_probe_count;

  int hash_function(const std::string &key) const;
  int find_slot(const std::string &key) const;
};

#endif // HASHTABLE_H
