#include <chrono>
#include <clocale>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <algorithm>

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

// Структура узла дерева
struct Knot {
    Train express;
    int height;
    Knot* R_Knot;
    Knot* L_Knot;

    Knot(Train& train) : express(train) {
        height = 1; 
        R_Knot = nullptr;
        L_Knot = nullptr;
    }
};

class AVL_Tree {
private:
    Knot* root;

    // Получение высоты узла
    int getHeight(Knot* knot) {
        return knot ? knot->height : 0;
    }

    // Получение фактора баланса
    int getBalance(Knot* knot) {
        return knot ? getHeight(knot->L_Knot) - getHeight(knot->R_Knot) : 0;
    }

    // Правый поворот
    Knot* rightRotate(Knot* y) {
        Knot* x = y->L_Knot;
        Knot* T2 = x->R_Knot;

        // Выполняем ротацию
        x->R_Knot = y;
        y->L_Knot = T2;

        // Обновляем высоты
        y->height = max(getHeight(y->L_Knot), getHeight(y->R_Knot)) + 1;
        x->height = max(getHeight(x->L_Knot), getHeight(x->R_Knot)) + 1;

        return x; // Новый корень
    }

    // Левый поворот
    Knot* leftRotate(Knot* x) {
        Knot* y = x->R_Knot;
        Knot* T2 = y->L_Knot;

        // Выполняем ротацию
        y->L_Knot = x;
        x->R_Knot = T2;

        // Обновляем высоты
        x->height = max(getHeight(x->L_Knot), getHeight(x->R_Knot)) + 1;
        y->height = max(getHeight(y->L_Knot), getHeight(y->R_Knot)) + 1;

        return y; // Новый корень
    }

    // Рекурсивная вставка
    Knot* insert(Knot* knot, Train train) {
        if (!knot) return new Knot(train);

        if (train.get_number() < knot->express.get_number()) {
            knot->L_Knot = insert(knot->L_Knot, train);
        } else if (train.get_number() > knot->express.get_number()) {
            knot->R_Knot = insert(knot->R_Knot, train);
        } else {
            return knot; // Дубликаты не допускаются
        }

        // Обновляем высоту узла
        knot->height = max(getHeight(knot->L_Knot), getHeight(knot->R_Knot)) + 1;

        // Получаем фактор баланса
        int balance = getBalance(knot);

        // Если узел стал несбалансированным, выполняем повороты
        // Левый левый случай
        if (balance > 1 && train.get_number() < knot->L_Knot->express.get_number()) {
            return rightRotate(knot);
        }

        // Правый правый случай
        if (balance < -1 && train.get_number() > knot->R_Knot->express.get_number()) {
            return leftRotate(knot);
        }

        // Левый правый случай
        if (balance > 1 && train.get_number() > knot->L_Knot->express.get_number()) {
            knot->L_Knot = leftRotate(knot->L_Knot);
            return rightRotate(knot);
        }

        // Правый левый случай
        if (balance < -1 && train.get_number() < knot->R_Knot->express.get_number()) {
            knot->R_Knot = rightRotate(knot->R_Knot);
            return leftRotate(knot);
        }

        return knot; 
    }

    // Рекурсивное удаление узла
    Knot* deleteNode(Knot* knot, int number) {
        if (!knot) return knot;

        if (number < knot->express.get_number()) {
            knot->L_Knot = deleteNode(knot->L_Knot, number);
        } else if (number > knot->express.get_number()) {
            knot->R_Knot = deleteNode(knot->R_Knot, number);
        } else {
            // Узел с одним или нулевым дочерним узлом
            if (!knot->L_Knot || !knot->R_Knot) {
                Knot* temp = knot->L_Knot ? knot->L_Knot : knot->R_Knot;

                // Если нет дочерних узлов
                if (!temp) {
                    temp = knot;
                    knot = nullptr;
                } else {
                    *knot = *temp; // Копируем содержимое
                }
                delete temp;
            } else {
                // Узел с двумя дочерними узлами
                Knot* temp = Find_Min(knot->R_Knot);
                knot->express = temp->express; // Копируем содержимое
                knot->R_Knot = deleteNode(knot->R_Knot, temp->express.get_number());
            }
        }

        // Если дерево стало пустым
        if (!knot) return knot;

        // Обновляем высоту узла
        knot->height = max(getHeight(knot->L_Knot), getHeight(knot->R_Knot)) + 1;

        // Получаем фактор баланса
        int balance = getBalance(knot);

        // Если узел стал несбалансированным, выполняем ротации
        // Левый левый случай
        if (balance > 1 && getBalance(knot->L_Knot) >= 0) {
            return rightRotate(knot);
        }

        // Левый правый случай
        if (balance > 1 && getBalance(knot->L_Knot) < 0) {
            knot->L_Knot = leftRotate(knot->L_Knot);
            return rightRotate(knot);
        }

        // Правый правый случай
        if (balance < -1 && getBalance(knot->R_Knot) <= 0) {
            return leftRotate(knot);
        }

        // Правый левый случай
        if (balance < -1 && getBalance(knot->R_Knot) > 0) {
            knot->R_Knot = rightRotate(knot->R_Knot);
            return leftRotate(knot);
        }

        return knot; 
    }

    // Нахождение минимального ключа
    Knot* Find_Min(Knot* c) {
        Knot* current_knot = c;
        while (current_knot && current_knot->L_Knot != nullptr)
            current_knot = current_knot->L_Knot;
        return current_knot;
    }

public:
    AVL_Tree() {
        root = nullptr;
    }

    Knot* get_root() { return root; }

    // Проверка на пустоту
    bool Is_Empty() {
        return root == nullptr;
    }

    // Добавление нового элемента
    void Add_Knot(Train train) {
        root = insert(root, train);
    }

    // Удаление узла
    void Pop_Knot(int number) {
        root = deleteNode(root, number);
    }

    // Вывод всех элементов дерева
    void Print_All() {
        if (Is_Empty()) {
            cout << "Дерево пустое." << endl;
            return;
        }
        stack<Knot*> Train_stack;
        Knot* current_root = root;
        while (current_root != nullptr || !Train_stack.empty()) {
            while (current_root != nullptr) {
                Train_stack.push(current_root);
                current_root = current_root->L_Knot;
            }
            current_root = Train_stack.top();
            Train_stack.pop();
            cout << current_root->express.get_number() << " " << current_root->express.get_next_station()
                 << " " << current_root->express.get_departure_time() << "\n";
            current_root = current_root->R_Knot;
        }
    }

    // Поиск узла
    Knot* Find_Train(int number) {
        Knot* current_knot = root;
        while (current_knot != nullptr) {
            if (current_knot->express.get_number() == number) {
                return current_knot;
            } else if (current_knot->express.get_number() < number) {
                current_knot = current_knot->R_Knot;
            } else {
                current_knot = current_knot->L_Knot;
            }
        }
        return nullptr;
    }

    // Поиск по станции
    void Find_By_Station(string station) {
        if (Is_Empty()) {
            cout << "Дерево пустое." << endl;
            return;
        }
        stack<Knot*> Train_stack;
        Knot* current_root = root;
        while (current_root != nullptr || !Train_stack.empty()) {
            while (current_root != nullptr) {
                Train_stack.push(current_root);
                current_root = current_root->L_Knot;
            }
            current_root = Train_stack.top();
            Train_stack.pop();
            if (current_root->express.get_next_station() == station) {
                cout << current_root->express.get_number() << "\n";
            }
            current_root = current_root->R_Knot;
        }
    }
};

int main() {
    
    setlocale(LC_ALL, "Russian");

    AVL_Tree trains;

    ifstream input_file("input_file.txt");
    if (!input_file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }

    int n;
    string s;
    int t;
    string line;
    while (getline(input_file, line)) {
        istringstream liner(line);
        char comma;
        if (liner >> n >> comma >> s >> t) {
            s.pop_back();
            Train trtrtr(n, s, t);
            trains.Add_Knot(trtrtr);
        } else {
            cout << "Ошибка разбора строки: " << line << "\n";
        }
    }

    // Проверка удаления узла
    // trains.Pop_Knot(130);

    // Проверка вывода всех узлов
    cout << "Все поезда:\n";
    trains.Print_All();
    auto start_time = std::chrono::high_resolution_clock::now(); // Начало измерения

    // Проверка поиска по значению
    Knot* ft = trains.Find_Train(3793);
    if (ft != nullptr)
        cout << "IT IS EXISTS\n"
             << ft->express.get_number() << " "
             << ft->express.get_next_station() << " " << ft->express.get_departure_time() << "\n";
    else
        cout << "IT IS NOT EXISTS\n";

    auto end_time = std::chrono::high_resolution_clock::now(); // Завершение измерения
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << endl;

    return 0;
}
