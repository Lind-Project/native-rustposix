# native-rustposix
Tools to compile native applications with the RustPOSIX library OS

## Building
Pull this repo, then
```
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```
Then compile the program by `python3 build.py pipe-cages`, for example.

## Write a c program
- `#include "lind_platform.h"` at top
- `lindrustinit(0)` at begining of `main`, `lindrustfinalize()` in the end
- calling lind syscalls, with the last parameter the cage number. Witout forking, we always use cage number 1.
- `lind_fork` merely duplicates the metadata of a cage, we still need to use native `pthread_create` to really spawn a new thread, in conjunction with `lind_fork`. Note that we still need to keep track of cage numbers outselves, and be careful about the heap and data, as there are no memory isolation at all.
- to make `lind_fork` work correctly, we also need to call `rustposix_thread_init(1, 0)` at the begining of `main`, as NaCl also call this to register the main thread of the App being started.


## `pipe-cages` Example
### Running `pipe-cages`
```
./pipe-cages {log2 of write buffer size} {log2 of read buffer size}
```
If no argument provided, the default is 16 for both args

### NOTE!
The `OUTLOOP = 1UL << 4` is just 8, so we will iterate the outer loop for 8 times, 8 * 2^30 bits = 1 GigaByte
