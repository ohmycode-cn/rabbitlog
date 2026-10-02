<p align="center">
  <img src="https://img.shields.io/badge/language-C%2B%2B20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++20"/>
  <img src="https://img.shields.io/badge/build-CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake"/>
  <img src="https://img.shields.io/badge/status-in%20development-orange?style=for-the-badge" alt="Status"/>
  <img src="https://img.shields.io/badge/license-MIT-green?style=for-the-badge" alt="License"/>
</p>

<h1 align="center">🐇 rabbitlog</h1>

<p align="center"><em>A modern C++ logging system — still under active development.</em></p>

---

**rabbitlog** is an independent branch derived from a standard-library submodule of
[ruacdb](https://github.com/ohmycode-cn/ruacdb). It aims to provide **high-performance,
high-concurrency** logging for modern C++ applications.

The project is currently in its early development stage, and progress may feel slow.
If rabbitlog is not yet where you need it to be — trust us, we are working on it.
**It is only a matter of time.**

Because the core library is still being designed and built, this README focuses on
what is **ready and usable today**: the project's shell tooling.

---

## 📚 Table of Contents

- [Requirements](#requirements)
- [Shell Scripts](#shell-scripts)
  - [`compile-project.sh`](#compile-projectsh--build-the-project)
  - [`test-compile-script.sh`](#test-compile-scriptsh--argument-combination-tests)
  - [`filter.sh`](#filtersh--export-the-api-framework)
  - [`mkf.sh`](#mkfsh--create-library-sourceheader-pairs)
  - [`mkf-test.sh`](#mkf-testsh--create-google-test-sourceheader-pairs)
- [Project Layout](#project-layout)
- [Status](#status)
- [License](#license)

---

## 🔧 Requirements

| Tool | Purpose |
|------|---------|
| **Bash 5.3+** | All scripts |
| **rsync** | `filter.sh` |
| **CMake 3.x** | `compile-project.sh` |
| **C++20** compatible compiler | Building the library |

---

## 🛠️ Shell Scripts

All scripts share a common logging layer (`.shared.sh`) and should be invoked with
`bash <script>` from the project root.

### `compile-project.sh` — Build the project

Builds rabbitlog via CMake. Unit tests are **enabled by default**.

```bash
# Default build (unit tests ON)
bash compile-project.sh

# Production build without unit tests
bash compile-project.sh --off-unit-test

# Clean build directory first, then build
bash compile-project.sh --clear-build

# Static linking (requires --off-unit-test)
bash compile-project.sh --static --off-unit-test

# Atomic guard with spinlock locking
bash compile-project.sh --off-unit-test --atomic --use-atomic-thread-spinlock

# Atomic guard alone — default std::mutex locking
bash compile-project.sh --off-unit-test --atomic
```

| Option | Description |
|--------|-------------|
| `--off-unit-test` | Disable unit tests and build a release binary. |
| `--clear-build` | Delete `build/*` before building. |
| `--static` | Statically link the binary. **Must** be combined with `--off-unit-test`. |
| `--atomic` | Optimization-parameter guard. Opens the optimization section: everything after it must be an optimization parameter (or end of arguments). Other options must appear **before** `--atomic`. |
| `--use-atomic-thread-spinlock` | Use `std::atomic_flag` spinlock locking in `OutputFile` instead of `std::mutex`. **Must** appear after `--atomic`. |

#### `--atomic` guard rules

`--atomic` is an **ordering guard**, not a CMake variable. It keeps optimization
parameters from being mixed up with build/layout options:

- Everything after `--atomic` must be an optimization parameter (currently
  `--use-atomic-thread-spinlock`), or the argument list must end.
- `--use-atomic-thread-spinlock` is rejected unless it follows `--atomic`.
- Other options (`--off-unit-test`, `--static`, `--clear-build`, ...) must be
  placed **before** `--atomic`.

```bash
# Valid — options first, guard, then optimization parameters
bash compile-project.sh --off-unit-test --static --atomic --use-atomic-thread-spinlock

# Invalid — --static after the guard
bash compile-project.sh --atomic --static

# Invalid — spinlock without the guard
bash compile-project.sh --use-atomic-thread-spinlock
```

When the spinlock optimization is enabled, the macro
`USE_ATOMIC_THREAD_SPINLOCK_MODE` is defined for the C++ sources and
`OutputFile` uses atomic spinlock locking instead of `std::mutex`.

---

### `test-compile-script.sh` — Argument-combination tests

Runs the `compile-project.sh` argument matrix: invalid `--atomic` guard
combinations must fail fast with a clear error, valid combinations must build
successfully and set the expected CMake spinlock flags.

```bash
# Run the full argument-combination test suite
bash test-compile-script.sh
```

The suite covers:

- **Invalid combinations** — spinlock without/after `--atomic`, non-optimization
  options after `--atomic`, `--static` without `--off-unit-test`, unknown flags.
- **Valid combinations** — `--atomic` alone, `--atomic --use-atomic-thread-spinlock`,
  static + spinlock, baseline release, default unit-test build.
- **CMakeCache assertions** — `ATOMIC_THREAD_SPINLOCK_MODE` is `ON`/`OFF` as
  expected and `ATOMIC_THREAD_MODE` is never written to the cache.

A `PASS`/`FAIL` line is printed per case, with a summary and non-zero exit code
on any failure.

---

### `filter.sh` — Export the API framework

Copies the pure API framework sources from `rbbl/` into a target directory,
excluding `main.cpp` and Google Test files. Useful for packaging or distributing
the library skeleton without test/build artifacts.

```bash
# Basic export
bash filter.sh --d /path/to/output

# Verbose — list every file transferred
bash filter.sh --d /path/to/output -v

# Remove old files in the target first, then export
bash filter.sh --d /path/to/output -v -r

# Show full help
bash filter.sh --help
```

| Option | Description |
|--------|-------------|
| `--d <dir>` | **Required.** Target directory. A `rbbl/` sub-directory is created inside it if missing. Use a complete path. |
| `-v` | Verbose mode — show each file transferred by rsync. |
| `-r` | Remove old files in `<target_dir>/rbbl` before filtering. |
| `--help`, `-h` | Show usage and exit. |

---

### `mkf.sh` — Create library source/header pairs

Scaffolds a `.cpp` / `.hpp` pair with the standard author banner and namespace
boilerplate. By default files go to `rbbl/src/` (cpp) and `rbbl/include/` (hpp).
Files are only created when **neither** the cpp nor the hpp already exists.

```bash
# Create rbbl/src/loader.cpp and rbbl/include/loader.hpp
bash mkf.sh --f loader

# Create in the API directory instead
bash mkf.sh --f rbbl --path api

# Create in the API library sub-directory
bash mkf.sh --f slog --path api/lib
```

| Option | Description |
|--------|-------------|
| `--f`, `--file <name>` | **Required.** Base file name without extension. |
| `--p`, `--path <loc>` | Optional output location. Accepted values: `api`, `api/lib`. Omit for the default `src`/`include` pair. |

---

### `mkf-test.sh` — Create Google Test source/header pairs

Same idea as `mkf.sh`, but for Google Test files under `test/google/`.
Default output is `test/google/src/` (cpp) and `test/google/include/` (hpp).

```bash
# Create test/google/src/loader_test.cpp and test/google/include/loader_test.hpp
bash mkf-test.sh --f loader_test

# Create in the interface (API test) directory
bash mkf-test.sh --f loader_test --path interface

# Short alias for interface
bash mkf-test.sh --f loader_test --path ife
```

| Option | Description |
|--------|-------------|
| `--f`, `--file <name>` | **Required.** Base file name without extension. |
| `--p`, `--path <loc>` | Optional output location. Accepted values: `interface`, `ife`. Omit for the default `src`/`include` pair. |

---

## 🗂️ Project Layout

```
rabbitlog/
├── rbbl/                  # Core library sources
│   ├── api/               # Public API layer
│   │   └── lib/           # API support library
│   ├── include/           # Public headers
│   └── src/               # Implementation files
├── test/
│   └── google/            # Google Test suite
│       ├── interface/     # API test interface
│       ├── include/
│       └── src/
├── build/                 # CMake build output
├── documents/             # Project documentation
├── compile-project.sh     # Build script
├── test-compile-script.sh # Argument-combination tests for the build script
├── filter.sh              # API framework export script
├── mkf.sh                 # Source/header scaffold script
├── mkf-test.sh            # Test source/header scaffold script
└── .shared.sh             # Shared logging helpers
```

---

## 🚧 Status

rabbitlog is **under active development**. The C++ logging core is not yet complete.
What you see here today is the development tooling that supports the build. The
library itself will grow into a high-performance, high-concurrency logging system
— we are not there yet, but we are getting there.

Contributions, feedback, and patience are all welcome.

## 📄 License

[MIT](LICENSE) © 2026 ohmycode-cn
