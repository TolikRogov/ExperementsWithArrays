CC = g++
CFLAGS= -c -D _DEBUG -D ADDR -ggdb3 -fsanitize=address -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -Werror=vla
LDFLAGS = -fsanitize=address

SOURCES = source
OBJECTS = build/main.o build/LinalLib.o

EXECUTABLE = mm
BUILD_DIR = build

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o  $@

$(BUILD_DIR)/%.o: $(SOURCES)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build/ mm
