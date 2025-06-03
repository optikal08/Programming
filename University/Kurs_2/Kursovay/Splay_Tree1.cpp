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

// Структура узла дерева
struct Node {
    Train express;

    Node* Parent;
    Node* R_Node;
    Node* L_Node;

    Node(Train& train) : express(train) {
        R_Node = nullptr;
        L_Node = nullptr;
        Parent = nullptr;
    }
};

class Splay_Tree {
private:
    Node* root;

public:
    Splay_Tree() {
        root = nullptr;
    }

    Node* get_root() { return root; }

    // Проверка на пустоту
    bool Is_Empty() {
        return root == nullptr;
    }

    // Добавление нового элента
    void Add_Knot(Node k) {
        Node* adder_node = new Node(k);
        Node* current_node = root;
        if (Is_Empty()) {
            root = adder_node;
        } else {
            bool flag = false;
            while (not flag) {
                if (adder_node->express.get_number() > current_node->express.get_number()) {
                    if (current_node->R_Node == nullptr) {
                        current_node->R_Node = adder_node;
                        adder_node->Parent = current_node;
                        flag = true;
                    } else {
                        current_node = current_node->R_Node;
                    }
                } else {
                    if (current_node->L_Node == nullptr) {
                        current_node->L_Node = adder_node;
                        adder_node->Parent = current_node;
                        flag = true;
                    } else {
                        current_node = current_node->L_Node;
                    }
                }
            }
        }

        Move_Knot_to_Root(adder_node);
    }

    // Вывод всех элементов дерева
    void Print_All() {
        if (root == nullptr) {
            cout << "Дерево пустое\n";
            return;
        }
        Node* current_node = root;
        stack<Node*> Train_stack;
        while (current_node != nullptr || !Train_stack.empty()) {
            while (current_node != 0) {
                Train_stack.push(current_node);
                current_node = current_node->L_Node;
            }

            current_node = Train_stack.top();
            Train_stack.pop();

            cout << current_node->express.get_number() << " " << current_node->express.get_next_station()
                 << " " << current_node->express.get_departure_time() << "\n";

            current_node = current_node->R_Node;
        }
    }

    // Поднятия узла в корень
    void Move_Knot_to_Root(Node* c) {
        Node* current_node = c;
        while (current_node != root) {
            Node* father = current_node->Parent;
            Node* grand_father;
            if (current_node->Parent == nullptr) {
                grand_father = nullptr;
                root = current_node;
                break;
            } else {
                grand_father = father->Parent;
            }

            if (grand_father == nullptr) { // малый поворот
                if (father->L_Node == current_node) {
                    father->L_Node = current_node->R_Node;
                    if (current_node->R_Node != nullptr)
                        current_node->R_Node->Parent = father;

                    current_node->R_Node = father;
                    father->Parent = current_node;
                    current_node->Parent = nullptr;
                } else {
                    father->R_Node = current_node->L_Node;
                    if (current_node->L_Node != nullptr)
                        current_node->L_Node->Parent = father;

                    current_node->L_Node = father;
                    father->Parent = current_node;
                    current_node->Parent = nullptr;
                }
            } else {
                // zig-zig левый
                if (grand_father->L_Node == father && father->L_Node == current_node) {
                    grand_father->L_Node = father->R_Node;
                    if (father->R_Node != nullptr)
                        father->R_Node->Parent = grand_father;

                    father->L_Node = current_node->R_Node;
                    if (current_node->R_Node != nullptr)
                        current_node->R_Node->Parent = father;
                    father->R_Node = grand_father;

                    current_node->Parent = grand_father->Parent;

                    if (current_node->Parent != nullptr) {
                        if (current_node->Parent->L_Node == grand_father)
                            current_node->Parent->L_Node = current_node;
                        else
                            current_node->Parent->R_Node = current_node;
                    }

                    grand_father->Parent = father;

                    father->Parent = current_node;

                    current_node->R_Node = father;
                }
                // zig-zig правый
                else if (grand_father->R_Node == father && father->R_Node == current_node) {
                    grand_father->R_Node = father->L_Node;
                    if (father->L_Node != nullptr)
                        father->L_Node->Parent = grand_father;

                    father->R_Node = current_node->L_Node;
                    if (current_node->L_Node != nullptr)
                        current_node->L_Node->Parent = father;
                    father->L_Node = grand_father;

                    current_node->Parent = grand_father->Parent;
                    if (current_node->Parent != nullptr) {
                        if (current_node->Parent->L_Node == grand_father)
                            current_node->Parent->L_Node = current_node;
                        else
                            current_node->Parent->R_Node = current_node;
                    }

                    grand_father->Parent = father;

                    father->Parent = current_node;

                    current_node->L_Node = father;
                }

                // zig-zag левый
                else if (grand_father->L_Node == father && father->R_Node == current_node) {
                    grand_father->L_Node = current_node->R_Node;
                    if (current_node->R_Node != nullptr)
                        current_node->R_Node->Parent = grand_father;

                    father->R_Node = current_node->L_Node;
                    if (current_node->L_Node != nullptr)
                        current_node->L_Node->Parent = father;

                    current_node->Parent = grand_father->Parent;
                    if (current_node->Parent != nullptr) {
                        if (current_node->Parent->L_Node == grand_father)
                            current_node->Parent->L_Node = current_node;
                        else
                            current_node->Parent->R_Node = current_node;
                    }

                    current_node->L_Node = father;
                    current_node->R_Node = grand_father;

                    father->Parent = current_node;
                    grand_father->Parent = current_node;
                }

                // zig-zag правый
                else if (grand_father->R_Node == father && father->L_Node == current_node) {
                    grand_father->R_Node = current_node->L_Node;
                    if (current_node->L_Node != nullptr)
                        current_node->L_Node->Parent = grand_father;

                    father->L_Node = current_node->R_Node;
                    if (current_node->R_Node != nullptr)
                        current_node->R_Node->Parent = father;

                    current_node->Parent = grand_father->Parent;
                    if (current_node->Parent != nullptr) {
                        if (current_node->Parent->L_Node == grand_father)
                            current_node->Parent->L_Node = current_node;
                        else
                            current_node->Parent->R_Node = current_node;
                    }

                    current_node->L_Node = grand_father;
                    current_node->R_Node = father;

                    father->Parent = current_node;
                    grand_father->Parent = current_node;
                }
            }
        }
    }

    // Поиск узла
    Node* Find_Train(int number) {
        Node* current_node = root;
        bool flag = false;
        while (not flag) {
            // cout << "!@#";
            // cout << current_node->express.get_number() << "\n";
            if (current_node->express.get_number() == number) {
                Move_Knot_to_Root(current_node);
                flag = true;
                return current_node;
            } else if (current_node->express.get_number() < number) {
                current_node = current_node->R_Node;
            } else if (current_node->express.get_number() > number) {
                current_node = current_node->L_Node;
            }
            if (current_node == nullptr) {
                flag = false;
                return nullptr;
            }
        }
        return 0;
    }

    // Нахождение максимального ключа
    Node* Find_Max(Node* c) {
        Node* current_node = c;
        while (current_node->R_Node != nullptr)
            current_node = current_node->R_Node;
        return current_node;
    }

    // Нахождение минимального ключа
    Node* Find_Min(Node* c) {
        Node* current_node = c;
        while (current_node->L_Node != nullptr)
            current_node = current_node->L_Node;
        return current_node;
    }

    // Поиск по значению
    Node* Find_By_Station(string station) {
        Node* current_root = root;
        stack<Node*> Train_stack;
        bool flag = false;
        while (current_root != nullptr) {
            // cout << current_root->express.get_number() << " " << current_root->express.get_next_station()
            // << " " << current_root->express.get_departure_time() << "\n";
            if (current_root->express.get_next_station() == station) {
                flag = true;
                return current_root;
            }
            if (current_root->L_Node != nullptr) {
                if (current_root->R_Node != nullptr) {
                    Train_stack.push(current_root->R_Node);
                }
                current_root = current_root->L_Node;
            } else if (current_root->R_Node != nullptr) {
                current_root = current_root->R_Node;
            } else {
                if (not Train_stack.empty()) {
                    current_root = Train_stack.top();
                    Train_stack.pop();
                } else {
                    current_root = nullptr;
                }
            }
        }
        if (not flag)
            return nullptr;
        return 0;
    }

    // Удаления узла
    void Pop_Knot(int number) {
        Node* deleted_knot = Find_Train(number);
        if (deleted_knot == nullptr)
            return;
        Move_Knot_to_Root(deleted_knot);
        // Node* current_node = deleted_knot;
        if (deleted_knot->L_Node == nullptr && deleted_knot->R_Node == nullptr) {
            root = nullptr;
            delete deleted_knot;
        } else if (deleted_knot->L_Node != nullptr && deleted_knot->R_Node == nullptr) {
            Node* current_node = deleted_knot->L_Node;
            root = current_node;
            current_node->Parent = nullptr;
            delete deleted_knot;
        } else if (deleted_knot->L_Node == nullptr && deleted_knot->R_Node != nullptr) {
            Node* current_node = deleted_knot->R_Node;
            root = current_node;
            current_node->Parent = nullptr;
            delete deleted_knot;
        } else if (deleted_knot->L_Node != nullptr && deleted_knot->R_Node != nullptr) {
            cout << deleted_knot->L_Node->express.get_number() << " " << deleted_knot->R_Node->express.get_number() << "\n";
            Node* current_node = deleted_knot->L_Node;
            current_node = Find_Max(current_node);
            if (current_node->Parent->R_Node == current_node) {
                current_node->Parent->R_Node = current_node->L_Node;
                if (current_node->L_Node != nullptr)
                    current_node->L_Node->Parent = current_node->Parent;

                current_node->L_Node = deleted_knot->L_Node;
                deleted_knot->L_Node->Parent = current_node;

                current_node->R_Node = deleted_knot->R_Node;
                if (deleted_knot->R_Node != nullptr)
                    deleted_knot->R_Node->Parent = current_node;
            } else {
                current_node->R_Node = deleted_knot->R_Node;
                if (deleted_knot->R_Node != nullptr)
                    deleted_knot->R_Node->Parent = current_node;
            }

            root = current_node;
            current_node->Parent = nullptr;
            delete deleted_knot;
        }
    }

    void Clear_Tree() {
        if (root == nullptr)
            return;

        stack<Node*> nodeStack;
        Node* current = root;
        Node* lastVisited = nullptr;

        while (current != nullptr || !nodeStack.empty()) {
            while (current != nullptr) {
                nodeStack.push(current);
                current = current->L_Node;
            }

            current = nodeStack.top();

            // Если правый узел существует и еще не был посещен, идем в него
            if (current->R_Node != nullptr && current->R_Node != lastVisited) {
                current = current->R_Node;
            } else {
                nodeStack.pop();
                delete current;
                lastVisited = current;
                current = nullptr;
            }
        }
        root = nullptr;
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

    // Проверка Print_All
    cout << "\n";
    trains.Print_All();
    cout << "\n";

    // Проверка Add_Knot
    Train test_train1(111, "SAMARA", 13);
    trains.Add_Knot(test_train1);

    

    // Проверка Pop_Knot
    trains.Pop_Knot(130);

    // trains.Find_Train(130);
    cout << "--------------\n";
    trains.Print_All();
    cout << "\n";

    // Проверка Find_Train
    Node* ft = trains.Find_Train(703);
    if (ft != nullptr)
        cout << "IT IS EXISTS\n"
             << ft->express.get_number() << " "
             << ft->express.get_next_station() << " " << ft->express.get_departure_time() << "\n";
    else
        cout << "IT IS NOT EXISTS\n";

    // Проверка поиска по станции
    // Node* st = trains.Find_By_Station("Kemerovo");
    // if (st != nullptr) {
    //     cout << st->express.get_number() << "\n";
    // }

    // Проверка очистки всего дерева
    // trains.Clear_Tree();
    // trains.Print_All();

}
