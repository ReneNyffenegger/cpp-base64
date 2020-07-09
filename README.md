# base64 (C++)

Base64 encoding and decoding with c++

## Using with CMake

The easiest way to use this project with CMake is by adding it as subfolder. To that aim, first either copy the files of this project or add it as git submodule to your project like this:

```bash
git submodule add -f https://github.com/eneNyffenegger/cpp-base64.git 3rdparty/cpp-base64
```

Then make the following modifications to your `CMakeLists.txt`:

```cmake
# Pick this line for an out-of-source submodule
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../3rdparty/cpp-base64/" cpp-base64)

# Pick this line instead if the library is inside your own source folder
add_subdirectory(cpp-base64)

# Add a dependency for any target that uses the library
target_link_libraries(your_target
    PRIVATE  # Add it to the PUBLIC section instead if you
             # include base64.h from a public header file
        base64::base64
    )
```

## See also

https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp
