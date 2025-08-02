CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

TARGET = s21_matrix.a
SOURCE_DIR = src/
HEADER_DIR = src/
LIB_DIR = .
TEST_DIR = tests/

SOURCE = $(SOURCE_DIR)s21_matrix.c
HEADER = $(HEADER_DIR)s21_matrix.h
TEST_SOURCE = $(TEST_DIR)test.c
TEST_EXECUTABLE = $(TEST_DIR)test_matrix

# Asosiy maqsad: kutubxonani yaratish
$(TARGET): $(SOURCE) $(HEADER)
	@mkdir -p $(LIB_DIR)
	@$(CC) $(CFLAGS) -c $(SOURCE) -o $(LIB_DIR)s21_matrix.o
	@ar rcs $(TARGET) $(LIB_DIR)s21_matrix.o
	@echo "Matritsa kutubxonasi 's21_matrix.a' yaratildi."

all: $(TARGET)

# Testlarni tuzish va ishga tushirish
test: $(TARGET) $(TEST_SOURCE)
	@$(CC) $(CFLAGS) $(TEST_SOURCE) $(TARGET) -o $(TEST_EXECUTABLE) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "Testlar tuzildi. Ishga tushirilmoqda..."
	@$(TEST_EXECUTABLE)

# Gcov hisobotini tuzish va yaratish
gcov_report: clean
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SOURCE) $(TEST_SOURCE) -o $(TEST_EXECUTABLE) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "Testlar gcov bayroqlari bilan tuzildi. Ishga tushirilmoqda..."
	@$(TEST_EXECUTABLE)
	@lcov -t "s21_matrix.h" -o $(TEST_DIR)coverage.info -c -d $(SOURCE_DIR)
	@genhtml -o $(TEST_DIR)report $(TEST_DIR)coverage.info
	@echo "Gcov hisoboti 'tests/report/index.html' da yaratildi."

# Tuzilgan fayllarni o'chirish
clean:
	@rm -f $(TARGET)
	@rm -f $(LIB_DIR)*.o
	@rm -f $(TEST_EXECUTABLE)
	@rm -rf $(TEST_DIR)report/
	@rm -f $(TEST_DIR)*.gcno $(TEST_DIR)*.gcda
	@rm -f $(SOURCE_DIR)*.gcno $(SOURCE_DIR)*.gcda
	@rm -f $(TEST_DIR)coverage.info
	@echo "Vaqtinchalik fayllar o'chirildi."

.PHONY: all test gcov_report clean