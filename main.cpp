#include <map>
#include <iostream>

template<typename K, typename V>
class IntervalMap {
  V default_value_;
	std::map<K, V> interval_map_;
public:
	IntervalMap(V const& val) : default_value_(val) {}
  
	void assign(K const& key_begin, K const& key_end, V const& val) {
    if (key_end < key_begin)
      return;

		using iterator_t = typename std::map<K, V>::iterator;
		iterator_t left_bound = interval_map_.lower_bound(key_begin);

		if (interval_map_.lower_bound(key_end) == interval_map_.begin()) {
			// very left case
			// no deletion required in case of overlapping on right margin
			interval_map_.insert({key_begin, val});
			interval_map_.insert({key_end, default_value_});
		} else {
			// in rest of the cases we need to
			// erase everything inside of inserted interval
			iterator_t right_bound = interval_map_.upper_bound(key_end);
			V last_val = std::prev(right_bound)->second;
			interval_map_.erase(left_bound, right_bound);
			interval_map_.insert({key_begin, val});
			interval_map_.insert({key_end, last_val});
		}
	}

	V const& operator[](K const& key) const {
		auto it = interval_map_.upper_bound(key);
		if (it == interval_map_.begin())
			return default_value_;
		else
			return (--it)->second;
	}

  void print() {
		std::cout << "============" << std::endl;
		for (auto item : interval_map_)
			std::cout << item.first << ", " << item.second << std::endl;
	}
};

void tests() {
	IntervalMap<int, char> imap {'a'};
	imap.assign(1, 4, 'b');
	imap.print();
	imap.assign(4, 7, 'c');
	imap.print();
	imap.assign(7, 10, 'd');
	imap.print();
	imap.assign(10, 15, 'e');
	imap.print();
	imap.assign(3, 7, 'e');
	imap.print();
	imap.assign(-10, -5, 'f');
	imap.print();
	imap.assign(-15, -10, 'g');
	imap.print();
	imap.assign(11, 200, 'h');
	imap.print();
	imap.assign(-26, 3, 'k');
	imap.print();
	imap.assign(-25, 200, 'l');
	imap.print();
	imap.assign(-25, 20, 's');
	imap.print();
}

int main() {
	tests();
	return 0;
}
