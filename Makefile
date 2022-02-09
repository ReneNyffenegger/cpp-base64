WARNINGS=                    \
   -Werror                   \
   -Wall                     \
   -Wextra                   \
   -pedantic                 \
   -Wcast-align              \
   -Wcast-qual               \
   -Wctor-dtor-privacy       \
   -Wdisabled-optimization   \
   -Wformat=2                \
   -Winit-self               \
   -Wlogical-op              \
   -Wmissing-include-dirs    \
   -Wmissing-declarations    \
   -Wnoexcept                \
   -Wold-style-cast          \
   -Woverloaded-virtual      \
   -Wredundant-decls         \
   -Wshadow                  \
   -Wsign-promo              \
   -Wstrict-null-sentinel    \
   -Wstrict-overflow=5       \
   -Wundef                   \
   -Wno-unused               \
   -Wno-variadic-macros      \
   -Wno-parentheses          \
   -fdiagnostics-show-option

test: base64-test-11 base64-test-17
	base64-test-11
	base64-test-17

base64-test-11: base64-11.o test-11.o
	g++ base64-11.o test-11.o -o $@

base64-test-17: base64-17.o test-17.o
	g++ base64-17.o test-17.o -o $@

base64-11.o: src/base64.cpp include/cpp-base64/base64.h
	g++ -std=c++11 $(WARNINGS) -c src/base64.cpp -o base64-11.o -I include

base64-17.o: src/base64.cpp include/cpp-base64/base64.h
	g++ -std=c++17 $(WARNINGS) -c src/base64.cpp -o base64-17.o -I include

test-11.o: test/test.cpp
	g++ -std=c++11 $(WARNINGS) -c test/test.cpp -o test-11.o -I include

test-17.o: test/test.cpp
	g++ -std=c++17 $(WARNINGS) -c test/test.cpp -o test-17.o -I include
