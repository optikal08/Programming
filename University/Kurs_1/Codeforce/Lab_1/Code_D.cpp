#include <cmath>
#include <iostream>
#include <string>
using namespace std;


// У Евлампия есть товарищ, который любит составлять шахматные этюды. Евлампий разрабатывает для него программу, которая проверяет корректность расстановки фигур на доске. В частности, эта программа выясняет, угрожает ли некоторому полю на доске какая-то фигура соперника.

// Для начала Евлампий решил рассмотреть три варианта для фигуры соперника: ладью, слона и ферзя.

// Ладья угрожает любому полю, которое находится на той же вертикали или на той же горизонтали, на которой стоит ладья.

// Слон угрожает любому полю, которое находится на какой-либо из двух диагоналей, пересечением которых является местоположение слона.

// Ферзь же угрожает любому полю, которому угрожала бы ладья или слон, если бы они находились на его месте.

// Ваша задача — по заданным координатам поля и фигуры на доске определить, угрожает ли фигура этому полю.

// Входные данные
// В первой строке содержится название фигуры соперника, для которой надо выполнить проверку: 𝑏𝑖𝑠ℎ𝑜𝑝 (слон), 𝑟𝑜𝑜𝑘 (ладья) или 𝑞𝑢𝑒𝑒𝑛 (ферзь).

// Во второй строке содержится позиция фигуры соперника в формате обычной шахматной нотации (символ и число без пробела), где символ (строчная латинская буква от 𝑎 до ℎ) означает номер вертикали, а число (от 1 до 8) — номер горизонтали.

// В третьей строке содержится описание поля, для которого надо выполнить проверку, в формате обычной шахматной нотации, описанной выше.

// Гарантируется, что фигура не стоит на поле, для которого надо выполнить проверку.

// Выходные данные
// Выведите слово 𝑌𝑒𝑠, если фигура угрожает полю, и 𝑁𝑜 в противном случае.

// Для вывода 𝑌𝑒𝑠 / 𝑁𝑜 можете использовать любой регистр символов (𝑌𝐸𝑆, 𝑦𝑒𝑠 и даже 𝑦𝐸𝑠 являются допустимыми вариантами).

int main() {
    // bishop, rook, queen
    string figure, enemyposition, pole;
    string b, c, bp, cp;
    int ech1, ech2, pch1, pch2;
    cin >> figure >> enemyposition >> pole;
    b = enemyposition[0];
    c = enemyposition[1];
    bp = pole[0];
    cp = pole[1];
    if (figure == "rook") {
        if (b == bp || c == cp) {
            cout << "yes";
        } else {
            cout << "no";
        }
    }
    switch (enemyposition[0]) {
    case 'a':
        enemyposition[0] = '1';
        break;
    case 'b':
        enemyposition[0] = '2';
        break;
    case 'c':
        enemyposition[0] = '3';
        break;
    case 'd':
        enemyposition[0] = '4';
        break;
    case 'e':
        enemyposition[0] = '5';
        break;
    case 'f':
        enemyposition[0] = '6';
        break;
    case 'g':
        enemyposition[0] = '7';
        break;
    case 'h':
        enemyposition[0] = '8';
        break;
    }
    switch (pole[0]) {
    case 'a':
        pole[0] = '1';
        break;
    case 'b':
        pole[0] = '2';
        break;
    case 'c':
        pole[0] = '3';
        break;
    case 'd':
        pole[0] = '4';
        break;
    case 'e':
        pole[0] = '5';
        break;
    case 'f':
        pole[0] = '6';
        break;
    case 'g':
        pole[0] = '7';
        break;
    case 'h':
        pole[0] = '8';
        break;
    }
    ech1 = (int)enemyposition[0];
    ech2 = (int)enemyposition[1];
    pch1 = (int)pole[0];
    pch2 = (int)pole[1];
    if (figure == "bishop") {
        if ((ech1 + ech2 == pch1 + pch2) || (ech1 - ech2 == pch1 - pch2)) {
            cout << "yes";
        } else {
            cout << "no";
        }
    }
    if (figure == "queen") {
        if ((b == bp || c == cp) || ((ech1 + ech2 == pch1 + pch2) || (ech1 - ech2 == pch1 - pch2))) {
            cout << "yes";
        } else {
            cout << "no";
        }
    }
}
