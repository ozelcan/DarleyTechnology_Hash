// HashTable.cpp
#include "HashTable.h"
#include <iostream>

HashTable::HashTable() : current_time(0), order_count(0), max_probe_count(0) {
  table.fill(Entry{});
  order.fill(-1);
  order_index.fill(-1);
}

int HashTable::hash_function(const std::string &key) const {
  const int p = 31;
  const int m = TABLE_SIZE;
  unsigned long long hash = 0, power = 1;
  for (char c : key) {
    hash = (hash + (c - 'a' + 1) * power) % m;
    power = (power * p) % m;
  }
  return static_cast<int>(hash);
}

int HashTable::find_slot(const std::string &key) const {
  int index = hash_function(key);
  int start_index = index;
  int probes = 0;

  while (table[index].timestamp != -1 && table[index].key != key) {
    index = (index + 1) % TABLE_SIZE;
    probes++;
    if (index == start_index)
      break; // full loop
  }

  if (probes > max_probe_count) {
    max_probe_count = probes;
  }

  return index;
}

void HashTable::insert(const std::string &key, int value) {
  int index = find_slot(key);
  bool is_new = (table[index].timestamp == -1);

  table[index].key = key;
  table[index].value = value;
  table[index].timestamp = current_time++;

  if (is_new) {
    order[order_count] = index;
    order_index[index] = order_count;
    order_count++;
  } else {
    int pos = order_index[index];
    int last_index = order[order_count - 1];
    std::swap(order[pos], order[order_count - 1]);
    order_index[index] = order_count - 1;
    order_index[last_index] = pos;
  }
}

void HashTable::remove(const std::string &key) {
  int index = find_slot(key);
  if (table[index].timestamp == -1)
    return;

  int pos = order_index[index];
  int last_index = order[order_count - 1];
  std::swap(order[pos], order[order_count - 1]);
  order_index[order[pos]] = pos;
  order_count--;

  table[index] = Entry{};
  order_index[index] = -1;
}

std::optional<int> HashTable::get(const std::string &key) const {
  int index = find_slot(key);
  if (table[index].timestamp == -1) {
    return std::nullopt;
  }
  return table[index].value;
}

std::optional<std::pair<std::string, int>> HashTable::get_first() const {
  if (order_count == 0)
    return std::nullopt;
  int first_index = order[0];
  const Entry &e = table[first_index];
  return {{e.key, e.value}};
}

std::optional<std::pair<std::string, int>> HashTable::get_last() const {
  if (order_count == 0)
    return std::nullopt;
  int last_index = order[order_count - 1];
  const Entry &e = table[last_index];
  return {{e.key, e.value}};
}

int HashTable::get_max_probe() const { return max_probe_count; }
