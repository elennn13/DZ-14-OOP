#include <iostream>
#include <cstring> // Для работы с C-строками
#include <stdexcept> // Для исключений

// Базовый класс String
class String {
private:
    char* str;         // Указатель на массив символов
    size_t size;       // Длина строки

public:
    // Конструктор по умолчанию
    String() : str(nullptr), size(0) {}

    // Конструктор, принимающий строку типа const char*
    String(const char* input) {
        if (input) {
            size = strlen(input);
            str = new char[size + 1]; // +1 для символа конца строки
            strcpy(str, input);
        }
        else {
            str = nullptr;
            size = 0;
        }
    }

    // Конструктор копирования
    String(const String& other) {
        size = other.size;
        str = new char[size + 1];
        strcpy(str, other.str);
    }

    // Оператор присваивания
    String& operator=(const String& other) {
        if (this != &other) { // Избегаем самоприсваивания
            delete[] str; // Освобождаем текущую память
            size = other.size;
            str = new char[size + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    // Метод получения длины строки
    size_t length() const {
        return size;
    }

    // Метод очистки строки
    void clear() {
        delete[] str; // Освобождаем память
        str = nullptr; // Обнуляем указатель
        size = 0;      // Устанавливаем размер в 0
    }

    // Деструктор
    ~String() {
        delete[] str; // Освобождаем память при уничтожении объекта
    }

    // Конкатенация строк (перегрузка оператора +)
    String operator+(const String& other) const {
        String result;
        result.size = size + other.size; // Обновляем размер
        result.str = new char[result.size + 1]; // +1 для символа конца строки

        // Копируем текущую строку и другую строку
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result; // Возвращаем новый объект
    }

    // Проверка на равенство
    bool operator==(const String& other) const {
        return (size == other.size) && (strcmp(str, other.str) == 0);
    }

    // Проверка на неравенство
    bool operator!=(const String& other) const {
        return !(*this == other); // Используем оператор == для проверки
    }

    // Метод для вывода строки (необязательный, для удобства)
    void print() const {
        if (str) {
            std::cout << str << std::endl;
        }
        else {
            std::cout << "Строка пуста." << std::endl;
        }
    }
};

// Производный класс BitString
class BitString : public String {
public:
    // Конструктор, принимающий строку типа const char*
    BitString(const char* input) : String() {
        if (input) {
            size_t len = strlen(input);
            // Проверка на наличие недопустимых символов
            for (size_t i = 0; i < len; ++i) {
                if (input[i] != '0' && input[i] != '1') {
                    clear(); // Очищаем строку, если есть недопустимые символы
                    return;
                }
            }
            // Если все символы допустимые, присваиваем строку
            this->str = new char[len + 1];
            strcpy(this->str, input);
            this->size = len;
        }
        else {
            this->str = nullptr;
            this->size = 0;
        }
    }

    // Переопределенный конструктор копирования
    BitString(const BitString& other) : String(other) {}

    // Переопределенный оператор присваивания
    BitString& operator=(const BitString& other) {
        String::operator=(other); // Используем оператор присваивания базового класса
        return *this;
    }
};