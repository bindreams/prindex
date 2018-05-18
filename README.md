# prindex
A simple, lightweight wrapper around C++'s `type_info` for consistent, cross-compiler usage.

Get the same `name()` and `hash_code()` on every (supported) compiler and standard library.
## Installation
Prindex is a single-header library. You can download the latest release [here](https://github.com/andreasxp/prindex/releases).
Using prindex requires support of C++11.
## Usage
Prindex was designed to be as similar in usage as `type_info` and `type_index`. Here is a table of different uses and their alternatives in prindex:

| C++ Standard                                    | prindex                                         |
| ----------------------------------------------- | ----------------------------------------------- |
| `typeid(type)`                                  | `prid<type>()`                                  |
| `typeid(expr)`                                  | `prid(expr)`                                    |
| `const type_info& ti = typeid(...)`             | `const prinfo& ti = prid(...)`                  |
| `type_index(typeid(...))`                       | `prindex(prid(...))` or `pridx(...)`            |

If you would like to take advantage of the *true keyword experience* you can define `PRINDEX_WANT_MACROS` before including the header and use `prid(type)` instead of `prid<type>()` (same for `pridx`). Please note that macros do not respect namespaces.

All interfaces of included classes are identical to the corresponding ones in the C++ Standard.

## License
This project is licenced under the MIT licence. It is free for personal and commercial use.
