#include <clocale>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
// kaka``
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

    Knot* R_Knot;
    Knot* L_Knot;

    Knot(Train& train) : express(train) {
        R_Knot = nullptr;
        L_Knot = nullptr;
    }
};

class Splay_Tree {
private:
    Knot* root;

public:
    Splay_Tree() {
        root = nullptr;
    }

    Knot* get_root() { return root; }

    // Проверка на пустоту
    bool Is_Empty() {
        return root == nullptr;
    }

    // Добавление нового элента
    void Add_Knot(Knot k) {
        Knot* adder_knot = new Knot(k);
        Knot* current_knot = root;
        if (Is_Empty()) {
            root = adder_knot;
        } else {
            bool flag = false;
            // cout << "root->express.get_number() = " << root->express.get_number() << "\n";
            while (not flag) {
                // i++;
                // cout << adder_knot->express.get_number() <<"\n";
                // cout << current_knot->express.get_number() << "\n";
                if (adder_knot->express.get_number() > current_knot->express.get_number()) {
                    // cout << "ALARM_ADD\n";
                    if (current_knot->R_Knot == nullptr) {
                        current_knot->R_Knot = adder_knot;
                        flag = true;
                    } else {
                        current_knot = current_knot->R_Knot;
                    }
                } else {
                    if (current_knot->L_Knot == nullptr) {
                        current_knot->L_Knot = adder_knot;
                        flag = true;
                    } else {
                        current_knot = current_knot->L_Knot;
                    }
                }
            }
        }
    }

    // Вывод всех элементов дерева
    void Print_All() {
        Knot* current_root = root;
        stack<Knot*> Train_stack;
        while (current_root != nullptr) {
            cout << current_root->express.get_number() << " " << current_root->express.get_next_station()
                 << " " << current_root->express.get_departure_time() << "\n";

            if (current_root->L_Knot != nullptr) {
                if (current_root->R_Knot != nullptr) {
                    Train_stack.push(current_root->R_Knot);
                }
                current_root = current_root->L_Knot;
            }

            else if (current_root->R_Knot != nullptr) {
                current_root = current_root->R_Knot;
            } else {
                if (not Train_stack.empty()) {
                    current_root = Train_stack.top();
                    Train_stack.pop();
                } else {
                    current_root = nullptr;
                }
            }
        }
    }

    // Поиск узла
    Knot* Find_Train(int number) {
        Knot* current_knot = root;
        bool flag = false;
        while (not flag) {
            // cout << "!@#";
            // cout << current_knot->express.get_number() << "\n";
            if (current_knot->express.get_number() == number) {
                flag = true;
                return current_knot;
            } else if (current_knot->express.get_number() < number) {
                current_knot = current_knot->R_Knot;
            } else if (current_knot->express.get_number() > number) {
                current_knot = current_knot->L_Knot;
            }
            if (current_knot == nullptr) {
                flag = false;
                return nullptr;
            }
        }
        return 0;
    }

    // Удаление узла
    void Pop_Knot(int number) {
        Knot* deleted_knot = root;
        Knot* current_knot = nullptr;
        Knot* father_knot = nullptr;

        if (deleted_knot == nullptr)
            return;

        // cout << "ALARMER\n";

        bool flag = false;
        while (deleted_knot != nullptr && deleted_knot->express.get_number() != number) {
            // cout << "deleted_knot = " << deleted_knot->express.get_number() << "\n";
            // cout << "ALARM1\n";
            if (deleted_knot->express.get_number() > number) {
                if (deleted_knot->L_Knot != nullptr) {
                    father_knot = deleted_knot;
                    deleted_knot = deleted_knot->L_Knot;
                    // cout << "1" << "\n";
                } else {
                    deleted_knot = nullptr;
                }
            } else if (deleted_knot->express.get_number() < number) {
                if (deleted_knot->R_Knot != nullptr) {
                    father_knot = deleted_knot;
                    deleted_knot = deleted_knot->R_Knot;
                    // cout << "2" << "\n";
                } else {
                    deleted_knot = nullptr;
                }
            }
        }
        // cout << "!@#\n";
        // cout << deleted_knot->express.get_number() << "\n";
        // cout << current_knot->express.get_number() << "\n";
        // cout << father_knot->express.get_number() << "\n";
        if (deleted_knot != nullptr) {
            if (deleted_knot->express.get_number() == number) {
                flag = true;
            }
        } else {
            cout << "Такого узла нет\n";
            return;
        }

        // cout << "deleted_knot = " << deleted_knot->express.get_number() << "\n";
        // cout << "father_knot = " << father_knot->express.get_number() << "\n";

        if (flag == true) {
            // cout << "ALARM2\n";
            // cout << deleted_knot->L_Knot->express.get_number() << " " << deleted_knot->R_Knot->express.get_number() << "\n";
            // Нет дочерних узлов
            if (deleted_knot->L_Knot == nullptr && deleted_knot->R_Knot == nullptr) {
                cout << "ALARM 1\n";
                if (father_knot != nullptr) {
                    if (father_knot->L_Knot == deleted_knot) {
                        father_knot->L_Knot = nullptr;
                        delete deleted_knot;
                    } else {
                        father_knot->R_Knot = nullptr;
                        delete deleted_knot;
                    }
                } else {
                    root = nullptr;
                    delete deleted_knot;
                }

            }

            // 1 дочерний узел
            else if ((deleted_knot->L_Knot != nullptr && deleted_knot->R_Knot == nullptr) || (deleted_knot->L_Knot == nullptr && deleted_knot->R_Knot != nullptr)) {
                // cout << "ALARM 2\n";
                if (deleted_knot->L_Knot != nullptr && deleted_knot->R_Knot == nullptr) {
                    if (father_knot == nullptr) {
                        root = nullptr;
                        delete deleted_knot;
                    } else if (father_knot->L_Knot == deleted_knot) {
                        father_knot->L_Knot = deleted_knot->L_Knot;
                        delete deleted_knot;
                    } else {
                        father_knot->R_Knot = deleted_knot->L_Knot;
                        delete deleted_knot;
                    }
                } else if (deleted_knot->L_Knot == nullptr && deleted_knot->R_Knot != nullptr) {
                    if (father_knot == nullptr) {
                        root = nullptr;
                        delete deleted_knot;
                    } else if (father_knot->L_Knot == deleted_knot) {
                        father_knot->L_Knot = deleted_knot->R_Knot;
                        if (deleted_knot == root) {
                            root = father_knot;
                        }
                        delete deleted_knot;
                    } else {
                        father_knot->R_Knot = deleted_knot->R_Knot;
                        if (deleted_knot == root) {
                            root = father_knot;
                        }
                        delete deleted_knot;
                    }
                }
            }

            // 2 дочених узла ???
            else if (deleted_knot->R_Knot != nullptr && deleted_knot->L_Knot != nullptr) {
                // cout << "ALARM 3\n";
                current_knot = Find_Max(deleted_knot->L_Knot);
                // cout << current_knot->express.get_number() << "!@#\n";
                if (deleted_knot->L_Knot->R_Knot != nullptr) {
                    // cout << "al1\n";
                    Knot* current_father = deleted_knot->L_Knot;
                    while (current_father->R_Knot != current_knot) {
                        current_father = current_father->R_Knot;
                        // cout << "123";
                    }
                    // cout << current_father->express.get_number() << "\n";
                    current_father->R_Knot = current_knot->L_Knot;
                    if (father_knot != nullptr && father_knot->L_Knot == deleted_knot) {
                        father_knot->L_Knot = current_knot;
                    } else if (father_knot != nullptr) {
                        father_knot->R_Knot = current_knot;
                    } else {
                        root = current_knot;
                    }
                    // cout << deleted_knot->L_Knot->express.get_number() << "   123123123\n";
                    current_knot->L_Knot = deleted_knot->L_Knot;
                    current_knot->R_Knot = deleted_knot->R_Knot;
                    delete deleted_knot;
                } else {
                    // cout << "!@#\n";
                    if (father_knot != nullptr && father_knot->L_Knot == deleted_knot) {
                        father_knot->L_Knot = current_knot;
                    } else if (father_knot != nullptr) {
                        father_knot->R_Knot = current_knot;
                    } else {
                        // cout << "(*^%)\n";
                        root = current_knot;
                    }
                    current_knot->L_Knot = nullptr;
                    current_knot->R_Knot = deleted_knot->R_Knot;
                    delete deleted_knot;
                }
            }
        }
    }

    // Нахождение максимального ключа
    Knot* Find_Max(Knot* c) {
        Knot* current_knot = c;
        while (current_knot->R_Knot != nullptr)
            current_knot = current_knot->R_Knot;
        return current_knot;
    }

    // Нахождение минимального ключа
    Knot* Find_Min(Knot* c) {
        Knot* current_knot = c;
        while (current_knot->L_Knot != nullptr)
            current_knot = current_knot->L_Knot;
        return current_knot;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Splay_Tree trains;

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
        // cout << "Читаем строку: " << line << "\n";
        istringstream liner(line);
        char comma;
        if (liner >> n >> comma >> s >> t) {
            s.pop_back();
            Train trtrtr(n, s, t);
            trains.Add_Knot(trtrtr);
            // cout << "Добавлен поезд: " << trtrtr.get_number() << endl;
        } else {
            cout << "Ошибка разбора строки: " << line << "\n";
        }
    }

    // Проверка Add_Knot
    Train test_train1(2000, "SAMARA", 13);
    trains.Add_Knot(test_train1);

    Train test_train2(111, "SAMARA", 13);
    trains.Add_Knot(test_train2);

    trains.Print_All();
    cout << "\n";

    // Проверка Pop_Knot
    trains.Pop_Knot(130);

    // Проверка Print_All
    trains.Print_All();
    cout << "\n";

    // // trains.Find_Train(130);
    // cout << "-----------\n";
    // trains.Print_All();
    // cout << "\n";

    // // Проверка Find_Train
    // Knot* ft = trains.Find_Train(111);
    // if (ft != nullptr) cout << "IT IS EXISTS\n" << ft->express.get_number() << " "
    //     << ft->express.get_next_station() << " " << ft->express.get_departure_time() << "\n";
    // else cout << "IT IS NOT EXISTS\n";

    // // Проверка поиска по станции
    // Knot* st = trains.Find_By_Station("Kemerovo");
    // if (st != nullptr) {
    //     cout << st->express.get_number() << "\n";
    // }
}
