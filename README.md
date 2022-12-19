# ft_containers
This project is about re-implementing some of the C++ standard template library containers.

All the C++98 features of the containers had to be implemented. Usage of C++98 was mandatory.

## Implemented containers
- vector (without vector<bool> specialization)
- map
- stack
- set (with a Red-Black tree as underlying data structure)

## Also implemented
- std::iterator_traits
- std::reverse_iterator
- std::enable_if (in a C++98 manner)
- std::is_integral
- std::equal
- std::lexicographical_compare
- std::pair
- std::make_pair

References used [CPlusPlus STL](https://cplusplus.com/reference/stl/) and [cppreference Containers library](https://en.cppreference.com/w/cpp/container).

## Usage
Run test script from the root of the repository `./tests/test.sh` to start test1, test2, and test3.

The tests will first create an output file using the std containers, then running the same tests using the re-implemented version. Finally comparing both output files.
