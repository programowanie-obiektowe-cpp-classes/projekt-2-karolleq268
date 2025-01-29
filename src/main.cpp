#include "PrintHello.hpp"

#include <iostream>
#include <vector>
#include <cctype> // dla std::toupper i ::isspace

// Wzorcowa klasa String
template <typename T>
class String {
protected:
    std::vector<T> data;

public:
    // Konstruktor domyślny
    String() {
        //std::cout << "Base constructor called \n";
    } // zostanie automatycznie stworzony pusty wektor std::vector<T>

    // Konstruktor z ciągiem znaków C-style (jeśli typ T to char)
    String(const T* str) {
        while (str != nullptr && *str != '\0') {
            data.push_back(*str);
            str++;
        }
        //std::cout << "Base constructor with string called \n";
    }

    // Operator + do łączenia dwóch obiektów
    String operator+(const String& other) const {
        String result;
        result.data = data;
        result.data.insert(result.data.end(), other.data.begin(), other.data.end());
        return result;
    }

    // Funkcja dodająca element na końcu
    void add_char_to_end(T c) {
        data.push_back(c);
    }

    // Funkcja dodająca element na początku
    void add_char_to_beginning(T c) {
        data.insert(data.begin(), c);
    }

    // Funkcja usuwająca ostatni element
    void remove_last_char() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    // Funkcja usuwająca pierwszy element
    void remove_first_char() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }

    // Funkcja usuwająca i-ty element
    void remove_char_at(size_t index) {
        if (index < data.size()) {
            data.erase(data.begin() + index); // data.begin wskazuje na pierwszy element, przesuwamy wskaznik o index
        }
    }

    // Funkcja dodająca element na i-tą pozycję
    void add_char_at(T c, size_t index) {
        if (index <= data.size()) {
            data.insert(data.begin() + index, c);
        }
    }

    // Funkcja do usunięcia białych znaków na początku i końcu (dla char, ale można dopasować do innych typów)
    String& trim() {
        auto start = std::find_if_not(data.begin(), data.end(), ::isspace); // zwraca pierwszy znak od początku nie będący znakiem białym
        auto end = std::find_if_not(data.rbegin(), data.rend(), ::isspace).base(); // .base() przekształca reverse iterator na normalny iterator
        data.assign(start, end); // "obcina" wektor do start i end
        return *this;
    }

    // Funkcja reverse (odwrócenie ciągu)
    void reverse() {
        std::reverse(data.begin(), data.end());
    }

    // Funkcja zwracająca długość łańcucha
    size_t length() const {
        return data.size();
    }

    // Funkcja wypisująca zawartość łańcucha
    void print() const {
        for (const auto& it : data) {
            std::cout << it;
        }
        std::cout << std::endl;
    }

    // Setter
    void set(const T* str) {
        data.clear();  // Usuwamy poprzednie dane
        while (str != nullptr && *str != '\0') {
            data.push_back(*str);
            str++;
        }
    }
};

// Klasa dziedzicząca po wzorcowej klasie String
template <typename T>
class Derived_String : public String<T> {
public:
    // Konstruktor w klasie pochodnej
    Derived_String() : String<T>() { // Wywołanie konstruktora klasy bazowej
        //std::cout << "Derived constructor called \n";
    }

    // Konstruktor w klasie pochodnej z ciągiem znaków
    Derived_String(const T* str) : String<T>(str) { // Wywołanie konstruktora klasy bazowej z parametrem
        //std::cout << "Derived constructor with string called \n";
    }

    // nowe funkcje wzgledem klasy bazowej

    // Zamiana na duże litery
    void to_uppercase() {
        for (auto& it : this->data) {
            it = std::toupper(it);
        }
    }

    // Zamiana na małe litery
    void to_lowercase() {
        for (auto& it : this->data) {
            it = std::tolower(it);
        }
    }
};

int main() {
    String<char> str1;

    str1.set("Ania");
    str1.print();

    str1.add_char_to_end('k');
    str1.print();

    str1.add_char_to_beginning('k');
    str1.print();

    str1.add_char_at('k', 2);
    str1.print();

    str1.remove_first_char();
    str1.print();

    str1.remove_last_char();
    str1.print();

    str1.remove_char_at(3);
    str1.print();

    str1.reverse();
    str1.print();

    std::cout << str1.length() << std::endl;

    printf("\n");

    String<char> str2(" Ala ");
    str2.print();

    std::cout << "Dlugosc poczatkowa: " << str2.length() << std::endl; // 5

    int n = str2.trim().length(); // jednoczesnie usuwamy biale znaki i zwracamy nowa dlugosc
    std::cout << "Dlugosc po trim(): " << n << std::endl; // 3
    str2.print();

    printf("\n");
    Derived_String<char> str3("Basia");
    str3.to_uppercase();
    str3.print();

    str3.to_lowercase();
    str3.print();

    printf("\n");
    String<char> str4("Hello");
    String<char> str5(" World");
    String<char> result = str4 + str5;
    result.print();

    String<char> str6("Halo");
    Derived_String<char> str7(" Welt");
    String<char> result2 = str6 + str7;
    result2.print();


    return 0;
}
