target_traits.hpp
=================
This header provides information on the build target. The interface is based on `<type_traits>`

Enums
-----
```cpp
enum target_system_name {
  target_system_windows,
  target_system_linux,
  target_system_mac,
  target_system_iphone,
  target_system_unknown
};

enum target_compiler_name {
  target_compiler_gcc,
  target_compiler_msc,
  target_compiler_unknown
};

enum target_cpu_name {
  target_cpu_ia32,
  target_cpu_amd64,
  target_cpu_unknown
};
```

Templates
---------
```
target_system_is_windows<T>;
target_system_is_linux<T>;
target_system_is_mac<T>;
target_system_is_iphone<T>;
target_system_is_unknown<T>;

target_compiler_is_gcc<T>;
target_compiler_is_msc<T>;
target_compiler_is_unknown<T>;

target_cpu_is_ia32<T>;
target_cpu_is_amd64<T>;
target_cpu_is_unknown<T>;
```

Use them like `<type_traits>`
```
// returns true
target_system_is_linux<target_system_linux>::value

// returns false
target_system_is_windows<target_system_linux>::value

// use without parameter to use automatically determined target values
target_system_is_linux<>::value
```
