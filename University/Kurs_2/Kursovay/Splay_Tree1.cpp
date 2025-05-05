#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 
#include <clocale>

using namespace std;

// класс, описывающий информацию поездов
class Train { 
    private:
        int number; // номер поезда 
        string next_station; // следущая станция
        int departure_time; // время отправления
    public:
        Train(int n, string s, int t) {
            number = n;
            next_station = s;
            departure_time = t;
        }
    
        int get_number() {return number;}
        string get_next_station() {return next_station;}
        int get_departure_time() {return departure_time;}
};
    
// Структура узла дерева
struct Knot { 
    Train express;
    
    Knot* Parent;
    Knot* R_Knot;
    Knot* L_Knot;
    
    Knot (Train& train):express(train){
        R_Knot = nullptr;
        L_Knot = nullptr;
        Parent = nullptr;
    }
};

class Splay_Tree {
private:
    Knot* root;
    
public:
    Splay_Tree() {
        root = nullptr;
    }
    
    Knot* get_root() {return root;}
    
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
        }
        else {
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
                        adder_knot->Parent = current_knot;
                        flag = true;
                    }
                    else {
                        current_knot = current_knot->R_Knot;
                    }
                }
                else {
                    if (current_knot->L_Knot == nullptr) {
                        current_knot->L_Knot = adder_knot;
                        adder_knot->Parent = current_knot;
                        flag = true;
                    }
                    else {
                        current_knot = current_knot->L_Knot;
                    }
                }
            }
        }

        Move_Knot_to_Root(adder_knot);
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
            else if (current_root->R_Knot != nullptr){
                current_root = current_root->R_Knot;
            }
            else {
                if (not Train_stack.empty()) {
                    current_root = Train_stack.top();
                    Train_stack.pop();
                }
                else {
                    current_root = nullptr;
                }
            }
        }
    }

    // Поднятия узла в корень
    void Move_Knot_to_Root(Knot* c) {
        Knot* current_knot = c;
        while (current_knot != root) {
            Knot* father = current_knot->Parent;
            Knot* grand_father;
            if (current_knot->Parent == nullptr) {
                grand_father = nullptr;
                root = current_knot;
                break;
            }
            else {
                grand_father = father->Parent;
            }

            if (grand_father == nullptr) { // малый поворот
                if (father->L_Knot == current_knot) {
                    father->L_Knot = current_knot->R_Knot;
                    if (current_knot->R_Knot != nullptr) current_knot->R_Knot->Parent = father;
                    
                    current_knot->R_Knot = father;
                    father->Parent = current_knot;
                    current_knot->Parent = nullptr;
        
                }
                else {
                    father->R_Knot = current_knot->L_Knot;
                    if (current_knot->L_Knot != nullptr) current_knot->L_Knot->Parent = father;

                    current_knot->L_Knot = father;
                    father->Parent = current_knot;
                    current_knot->Parent = nullptr;
                    
                }
            }
            else {
                // zig-zig левый
                if (grand_father->L_Knot == father && father->L_Knot == current_knot) {
                    grand_father->L_Knot = father->R_Knot;
                    if (father->R_Knot != nullptr) father->R_Knot->Parent = grand_father;

                    father->L_Knot = current_knot->R_Knot;
                    if (current_knot->R_Knot != nullptr) current_knot->R_Knot->Parent = father;
                    father->R_Knot = grand_father;

                    current_knot->Parent = grand_father->Parent;

                    if (current_knot->Parent != nullptr) {
                        if (current_knot->Parent->L_Knot == grand_father) current_knot->Parent->L_Knot = current_knot;
                        else current_knot->Parent->R_Knot = current_knot;
                    }

                    grand_father->Parent = father;

                    father->Parent = current_knot;

                    current_knot->R_Knot = father;
                }
                // zig-zig правый
                else if (grand_father->R_Knot == father && father->R_Knot == current_knot) {
                    grand_father->R_Knot = father->L_Knot;
                    if (father->L_Knot != nullptr) father->L_Knot->Parent = grand_father;

                    father->R_Knot = current_knot->L_Knot;
                    if (current_knot->L_Knot != nullptr) current_knot->L_Knot->Parent = father;
                    father->L_Knot = grand_father;

                    current_knot->Parent = grand_father->Parent;
                    if (current_knot->Parent != nullptr) {
                        if (current_knot->Parent->L_Knot == grand_father) current_knot->Parent->L_Knot = current_knot;
                        else current_knot->Parent->R_Knot = current_knot;
                    }

                    grand_father->Parent = father;

                    father->Parent = current_knot;

                    current_knot->L_Knot = father;
                }

                // zig-zag левый
                else if (grand_father->L_Knot == father && father->R_Knot == current_knot) {
                    grand_father->L_Knot = current_knot->R_Knot;
                    if (current_knot->R_Knot != nullptr) current_knot->R_Knot->Parent = grand_father;

                    father->R_Knot = current_knot->L_Knot;
                    if (current_knot->L_Knot != nullptr) current_knot->L_Knot->Parent = father;

                    current_knot->Parent = grand_father->Parent;
                    if (current_knot->Parent != nullptr) {
                        if (current_knot->Parent->L_Knot == grand_father) current_knot->Parent->L_Knot = current_knot;
                        else current_knot->Parent->R_Knot = current_knot;
                    }

                    current_knot->L_Knot = father;
                    current_knot->R_Knot = grand_father;
        
                    father->Parent = current_knot;
                    grand_father->Parent = current_knot;
                }

                // zig-zag правый
                else if (grand_father->R_Knot == father && father->L_Knot == current_knot) {
                    grand_father->R_Knot = current_knot->L_Knot;
                    if (current_knot->L_Knot != nullptr) current_knot->L_Knot->Parent = grand_father;

                    father->L_Knot = current_knot->R_Knot;
                    if (current_knot->R_Knot != nullptr) current_knot->R_Knot->Parent = father;

                    current_knot->Parent = grand_father->Parent;
                    if (current_knot->Parent != nullptr){
                        if (current_knot->Parent->L_Knot == grand_father) current_knot->Parent->L_Knot = current_knot;
                        else current_knot->Parent->R_Knot = current_knot;
                    }
                    
                    current_knot->L_Knot = grand_father;
                    current_knot->R_Knot = father;
        
                    father->Parent = current_knot;
                    grand_father->Parent = current_knot;
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
                Move_Knot_to_Root(current_knot);
                flag = true;
                return current_knot;
            }
            else if (current_knot->express.get_number() < number) {
                current_knot = current_knot->R_Knot;
            }
            else if (current_knot->express.get_number() > number) {
                current_knot = current_knot->L_Knot;
            }
            if (current_knot == nullptr) {
                flag = false;
                return nullptr;
            }
        }
        return 0;
    }

    // Нахождение максимального ключа
    Knot* Find_Max(Knot* c) {
        Knot* current_knot = c;
        while (current_knot->R_Knot != nullptr) current_knot = current_knot->R_Knot;
        return current_knot;
    }

    // Нахождение минимального ключа
    Knot* Find_Min(Knot* c) {
        Knot* current_knot = c;
        while(current_knot->L_Knot != nullptr) current_knot = current_knot->L_Knot;
        return current_knot;
    }
    
    // Поиск по значению
    Knot* Find_By_Station(string station) {
        Knot* current_root = root;
        stack<Knot*> Train_stack;
        bool flag = false;
        while (current_root != nullptr) {
            // cout << current_root->express.get_number() << " " << current_root->express.get_next_station() 
            // << " " << current_root->express.get_departure_time() << "\n";
            if (current_root->express.get_next_station() == station) {
                flag = true;
                return current_root;
            }
            if (current_root->L_Knot != nullptr) {
                if (current_root->R_Knot != nullptr) {
                    Train_stack.push(current_root->R_Knot);
                }
                current_root = current_root->L_Knot;
            }
            else if (current_root->R_Knot != nullptr){
                current_root = current_root->R_Knot;
            }
            else {
                if (not Train_stack.empty()) {
                    current_root = Train_stack.top();
                    Train_stack.pop();
                }
                else {
                    current_root = nullptr;
                }
            }
        }
        if (not flag) return nullptr;
        return 0;
    }

    // Удаления узла
    void Pop_Knot(int number) {
        Knot* deleted_knot = Find_Train(number);
        if (deleted_knot == nullptr) return;
        Move_Knot_to_Root(deleted_knot);
        // Knot* current_knot = deleted_knot;
        if (deleted_knot->L_Knot == nullptr && deleted_knot->R_Knot == nullptr) {
            root = nullptr;
            delete deleted_knot;
        }
        else if (deleted_knot->L_Knot != nullptr && deleted_knot->R_Knot == nullptr) {
            Knot* current_knot = deleted_knot->L_Knot;
            root = current_knot;
            current_knot->Parent = nullptr;
            delete deleted_knot;
        }
        else if (deleted_knot->L_Knot == nullptr && deleted_knot->R_Knot != nullptr) {
            Knot* current_knot = deleted_knot->R_Knot;
            root = current_knot;
            current_knot->Parent = nullptr;
            delete deleted_knot;
        }
        else if (deleted_knot->L_Knot != nullptr && deleted_knot->R_Knot != nullptr) {
            cout << deleted_knot->L_Knot->express.get_number() << " " << deleted_knot->R_Knot->express.get_number() << "\n";
            Knot* current_knot = deleted_knot->L_Knot;
            current_knot = Find_Max(current_knot);
            if (current_knot->Parent->R_Knot == current_knot) {
                current_knot->Parent->R_Knot = current_knot->L_Knot;
                if (current_knot->L_Knot != nullptr) current_knot->L_Knot->Parent = current_knot->Parent;

                current_knot->L_Knot = deleted_knot->L_Knot;
                deleted_knot->L_Knot->Parent = current_knot;

                current_knot->R_Knot = deleted_knot->R_Knot;
                if (deleted_knot->R_Knot != nullptr) deleted_knot->R_Knot->Parent = current_knot;
            }
            else {
                current_knot->R_Knot = deleted_knot->R_Knot;
                if (deleted_knot->R_Knot != nullptr) deleted_knot->R_Knot->Parent = current_knot;
            }

            root = current_knot;
            current_knot->Parent = nullptr;
            delete deleted_knot;

        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Splay_Tree trains;

    ifstream input_file("input_file.txt");
    if (!input_file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;    }

    int n;
    string s;
    int t;
    string line;
    while (getline(input_file, line)) {
        cout << "Читаем строку: " << line << "\n";
        istringstream liner(line);
        char comma;
        if (liner >> n >> comma >> s >> t) {
            s.pop_back();
            Train trtrtr(n, s, t);
            trains.Add_Knot(trtrtr);            
            // cout << "Добавлен поезд: " << trtrtr.get_number() << endl;
        } 
        else {
           cout << "Ошибка разбора строки: " << line << "\n";
       }
   }

    // Проверка Add_Knot
    Train test_train1(111, "SAMARA", 13);
    trains.Add_Knot(test_train1);

    // Проверка Print_All
    trains.Print_All();
    cout << "\n";

    // Проверка Pop_Knot
    trains.Pop_Knot(130);

    // trains.Find_Train(130);
    cout << "-----------\n";
    trains.Print_All();
    cout << "\n";
    
    // Проверка Find_Train
    Knot* ft = trains.Find_Train(111);
    if (ft != nullptr) cout << "IT IS EXISTS\n" << ft->express.get_number() << " " 
        << ft->express.get_next_station() << " " << ft->express.get_departure_time() << "\n";
    else cout << "IT IS NOT EXISTS\n";
    
    // Проверка поиска по станции
    Knot* st = trains.Find_By_Station("Kemerovo");
    if (st != nullptr) {
        cout << st->express.get_number() << "\n";
    }
}
    