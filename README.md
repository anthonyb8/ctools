# Ctools

**Ctools** is a collection of generic data structures implemented in C.

Designed as an **educational resource**, Ctools offers idiomatic C implementations of common data structures. It uses `void*` to provide type-agnostic storage and sticks to the core C89/C99 standard, making it portable and easy to understand.

## 🧰 Data Structures Included

- **Vec** – A dynamic array
- **Map** – A simple hash map
- **Linked List** – A singly linked list implementation

All structures support **manual memory management**, putting you in full control of allocations and lifetimes.

## 🔧 Features

- Type-agnostic (`void*`-based) interfaces
- No external dependencies
- Dynamically resizing containers
- Simple, portable C89/C99-compatible code
- Minimal API surface for learning and extension

## 📂 Examples

Each data structure includes working demo files:

- [Vec](examples/vec.c)
- [Map](exmaples/map.c)
- [List](exmaples/list.c)

```bash
cmake .

./build/vecExample
./build/mapExample
./examples/listExample
```

## :computer: Usage

#### Option 1: Clone manually

```bash
git clone https://github.com/anthonyb8/cvec.git libs/cvec
```

#### Option 2: Add as a submodule

```bash
git submodule add https://github.com/anthonyb8/cvec.git libs/cvec
```

#### CMake Integration

```CMakeLists
add_subdirectory(libs/cvec)
target_link_libraries(my_app PRIVATE cvec)
```

## License

This project is licensed under the Apache 2.0 License. See the [LICENSE](LICENSE) file for details.
