## Overview
Amirkabir University of Technology 1400-2: Advanced Programming Course

- [x] HW1: Implement a Matrix class and associated functions
- [x] HW2: Implement a program that simulates the execution process of a cryptocurrency client/server
- [x] HW3: Implements a Binary Search Tree (BST)
- [x] HW4: Implements **shared_ptr** and **unique_ptr** smart pointers in C++
- [x] HW5: Implement multiple classes using inheritance and polymorphism
- [ ] ~~HW6: Solve 4 problems using the STL library~~
- [x] hw7: A python project

## Set Up

**This is for Linux or WSL**

1. Git clone the URL
2. Install **cmake**

```bash
sudo apt install cmake make 
```

3. Install [googletest](https://github.com/google/googletest/blob/main/googletest/README.md)

```bash
git clone https://github.com/google/googletest.git -b release-1.12.1
cd googletest # Main directory of the cloned repository.
mkdir build # Create a directory to hold the build output.
cd build
cmake .. # Generate native build scripts for GoogleTest.
make
sudo make install
```

4. Turn the value to `false`, uncomment the very part in `unit_test.cpp`

5. Compile

```bash
mkdir build
cd build
cmake ..
make
```









