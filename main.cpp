#include <iostream>

template<typename type>
class Stack {
private:
    char* Data = nullptr;

    // Текущее количество элементов в стеке
    unsigned int CurrentCount = 0;
    // Максимальное количество элементов, которое можно хранить в стеке
    unsigned int ElementsCount;
public:

    // 1. Конструктор с указанием размера стека
    explicit Stack(unsigned int size) : ElementsCount(size) {
        try {
            Data = new char[size * sizeof(type)];
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "Failed to allocate memory for the stack: " << e.what() << std::endl;
            ElementsCount = 0;
            throw;
        }
    }

    // Конструктор копирования
    Stack(const Stack<type>& copy) {
        Data = new char[copy.ElementsCount * sizeof(type)];
        CurrentCount = copy.CurrentCount;
        ElementsCount = copy.ElementsCount;
    }

    // Оператор присваивания
    Stack& operator= (Stack<type>& copy) {
        if (this != &copy) {
            Stack temp = copy;
            std::swap(Data, copy.Data);
            std::swap(CurrentCount, copy.CurrentCount);
            std::swap(ElementsCount, copy.ElementsCount);
        }
        return *this;
    }

    // 2. Метод size
    unsigned int size() const {
        return CurrentCount;
    }

    // 3. Метод empty – возвращает true или false
    bool empty() const {
        if (CurrentCount == 0) {
            return true;
        }
        return false;
    }

    // 4. Метод push, чтобы положить элемент в стек
    void push(const type& newElement) {
        if (CurrentCount < ElementsCount) {
            Data[CurrentCount] = newElement;
            CurrentCount++;
        }
        else {
            throw std::overflow_error("The stack is overflowing");
        }
    }

    // 5. Метод pop, чтобы извлечь элемент из стека
    type pop() {
        if (CurrentCount != 0) {
            CurrentCount--;
            return Data[CurrentCount];
        }
        throw std::out_of_range("Empty stack");
    }

    // 6. Метод top, чтобы посмотреть верхний элемент стека, но не извлекать его.
    type top() {
        if (CurrentCount != 0) {
            return Data[CurrentCount];
        }
        throw std::logic_error("Empty stack");
    }
    ~Stack() {
        delete[] Data;
    }
};


int main() {
    setlocale(LC_ALL, "Rus");
    Stack<int> first(1);
    try {
        first.push(1);
        first.push(2);
    }
    catch (const std::overflow_error& currentError) {
        std::cerr << "Превышено количество допустимых элементов: " << first.size() << std::endl;
    }
    Stack<int> second(1);
    try {
        second.pop();
    }
    catch (const std::logic_error& currentError) {
        std::cerr << "Ошибка: ";
        std::cerr << currentError.what() << std::endl;
    }
    return 0;
}