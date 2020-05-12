# PipeWrapper
A simple wrapper around C-style pipes written in C++ streams style.

### Features
* Easy to use (similar to `std::fstream`).
* Easy to implement.
* Minimal overhead.
* Supports manipulators such as `std::endl`.

### Usage
The PipeWrapper works similar to `std::fstream`. 

See the example usage bellow. You can find expanded example (with 'gnuplot' utility) in corresponding folder.

```cpp=
PipeWrapper pipe("gnuplot -persist", "w");

pipe << "Sample string\n" << 't' << '\n';
pipe << 5.7 << std::endl;

pipe.close();
```
