CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

# Находим все исходные файлы
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Имя исполняемого файла
TARGET = program

# Основные правила
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@

# Правило для объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Правило для зависимостей
-include $(DEPS)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean 