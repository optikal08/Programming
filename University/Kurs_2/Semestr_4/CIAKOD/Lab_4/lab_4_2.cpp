#include <chrono>
#include <clocale>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// класс, описывающий информацию поездов
class Train {
private:
    int number;          // номер поезда
    string next_station; // следущая станция
    int departure_time;  // время отправления
public:
    Train(int n, string s, int t) {
        number = n;
        next_station = s;
        departure_time = t;
    }

    int get_number() { return number; }
    string get_next_station() { return next_station; }
    int get_departure_time() { return departure_time; }
};

// Поиск по значению
void Find_By_Station(vector<Train> vec, string str) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].get_next_station() == str) {
            cout << vec[i].get_number() << "\n";
        }
    }
}

void Find_By_Number(vector<Train> vec, int num) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].get_number() == num) {
            cout << vec[i].get_number() << " " << vec[i].get_next_station() << "\n";
            break;
        }
    }
}

int main() {
    
    setlocale(LC_ALL, "Russian");

    vector<Train> trains;

    ifstream input_file("random_data.txt");
    if (!input_file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }
    

    int n;
    string s;
    int t;
    string line;
    while (getline(input_file, line)) {
        // cout << "Читаем строку: " << line << "\n";
        istringstream liner(line);
        char comma;
        if (liner >> n >> comma >> s >> t) {
            s.pop_back();
            Train trtrtr(n, s, t);
            trains.push_back(trtrtr);
            // cout << "Добавлен поезд: " << trtrtr.get_number() << endl;
        } else {
            cout << "Ошибка разбора строки: " << line << "\n";
        }
    }
    // sort(trains.begin(), trains.end(), [](Train a, Train b) {
    //     return a.get_number() < b.get_number();
    // });
    auto start_time = std::chrono::high_resolution_clock::now(); // Начало измерения
    

    Find_By_Number(trains, 4879);

    auto end_time = std::chrono::high_resolution_clock::now(); // Завершение измерения

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << std::endl;

    // Проверка поиска по значению
    // trains.Find_By_Station("Kemerovo");
}