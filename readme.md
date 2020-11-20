# Interval map implementation
## Description
`IntervalMap<K, V>` is a data structure that associates keys of type `K` with values of type `V`. It is designed to be used efficiently in situations where intervals of consecutive keys are associated with the same value. Goal is to implement the assign member function of this data structure, which is outlined below.

Each key-value-pair `(k, v)` in `IntervalMap<K, V>::interval_map_` means that the value `v` is associated with all keys from `k` (including) to the next key (excluding) in `interval_map_`. The member `IntervalMap<K, V>::default_value_` holds the value that is associated with all keys less than the first key in `interval_map_`.

### Example
Let `IM` be an instance of `IntervalMap<int,char>` where

- `M.default_value_=='A'`
- `M.interval_map_=={ (1,'B'), (3,'A') }`

then `IM` represents the mapping

```
-2 -> 'A'
-1 -> 'A'
0 -> 'A'
1 -> 'B'
2 -> 'B'
3 -> 'A'
4 -> 'A'
5 -> 'A'
```

The representation in the std::map must be canonical, that is, consecutive map entries must not contain the same value: `..., (3,'A'), (5,'A'), ...` is not allowed. Likewise, the first entry in `interval_map_` must not contain the same value as `default_value_`. Initially, the whole range of `K` is associated with a given initial value, passed to the constructor of the `IntervalMap<K, V>` data structure.

### Key type `K`
- besides being copyable and assignable, is less-than comparable via operator<
- does not implement any other operations, in particular no equality comparison or arithmetic operators

### Value type `V`
- besides being copyable and assignable, is equality-comparable via operator==
- does not implement any other operations


- **Type requirements are met:** You must adhere to the specification of the key and value type given above.
- **Correctness:** Your program should produce a working IntervalMap with the behavior described above. In particular, pay attention to the validity of iterators. It is illegal to dereference end iterators. Consider using a checking STL implementation such as the one shipped with Visual C++ or GCC.
- **Canonicity:** The representation in `interval_map_` must be canonical.
- **Running time:** Imagine your implementation is part of a library, so it should be big-O optimal. In addition:
  - Do not make big-O more operations on K and V than necessary, because you do not know how fast operations on `K / V` are; remember that constructions, destructions and assignments are operations as well.
  - Do not make more than two operations of amortized `O(log N)`, in contrast to `O(1)`, running time, where N is the number of elements in `interval_map_`.
  - Otherwise favor simplicity over minor speed improvements.