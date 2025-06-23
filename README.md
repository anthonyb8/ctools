# Cvec

**Cvec** is a simple, generic dynamic array implementation in C.

Designed primarily as an **educational tool**, Cvec is written in idiomatic C, has no external dependencies and uses `void*` internally to allow storage of any data type.

## 🔧 Features

- Type-agnostic storage (via `void*`)
- Dynamically resizes when needed
- Manual memory management (you control lifetimes)
- C89/C99-compatible

## 📦 Example

```c
#include "cvec/cvec.h"
#include <stdio.h>

int main() {
    Vec vec = vec_new(sizeof(int));

    int x = 42;
    vec_push(&vec, &x);

    int out;
    if (vec_pop(&vec, &out) == 0) {
        printf("Popped: %d\n", out);
    }

    vec_free(&vec);
    return 0;
}
```

\*See more use cases [here](examples/demo.c)

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
