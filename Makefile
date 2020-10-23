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

base64-11.o: base64.cpp base64.h
	g++ -std=c++11 $(WARNINGS) -c base64.cpp -o base64-11.o

base64-17.o: base64.cpp base64.h
	g++ -std=c++17 $(WARNINGS) -c base64.cpp -o base64-17.o

test-11.o: test.cpp
	g++ -std=c++11 $(WARNINGS) -c test.cpp -o test-11.o

test-17.o: test.cpp
	g++ -std=c++17 $(WARNINGS) -c test.cpp -o test-17.o
