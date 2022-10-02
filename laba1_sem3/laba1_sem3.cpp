#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <clocale>
#include <Windows.h>
#include <fstream>
using namespace std;

class Dh_Enc {
public:
    int p;
    int g;
    void DifHelm_encr(string text) {
        cout << "Выберите p такое, что p-простое число: ";
        cin >> p;
        cout << "Выберите g < p-1: ";
        cin >> g;
        cout << "Введите xb: ";
        int in_b;
        cin >> in_b;
        input_b(in_b);
        ya = ost(g, xa, p);
        cout << "ya = " << ya << endl;
        yb = ost(g, xb, p);
        key = ost(yb, xa, p);
        cout << encryption(text, key);
    }
private:
    int xa;
    int xb;
    int ya;
    int yb;
    int key;
    int ost(int a, int x, int n) {
        int res = 1;
        for (int i = 0; i <= x; i++) {
            res = res * a;
            res %= n;
        }
        return res;
    }

    void input_b(int s) {
        xb = s;
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(2, p - 1);
        xa = dist(gen);
    }

    string encryption(string str, int key) {
        string res="";
        for (auto i : str) {
            res += char(int(i) + key);
        }
        return res;
    }
};
class Dh_Dec {
public:
    void DifHelm_decr() {
        cout << "Введите ya: ";
        cin >> ya;
        cout << "Введите xb: ";
        cin >> xb;
        cout << "Введите p: ";
        cin >> p;


        int key = ost(ya, xb, p);
        string text;

        cin.get();
        cout << "Сообщение для расшифровки: ";
        getline(cin, text);
        cout << decryption(text, key);

    }
private:
    int p = 0;
    int ya = 0;
    int xb = 0;
    int ost(int a, int x, int n) {
        int res = 1;
        for (int i = 0; i <= x; i++) {
            res = res * a;
            res %= n;
        }
        return res;
    }
    string decryption(string str, int key) {
        string res = "";
        for (auto i : str) {
            res += char(int(i) - key);
        }
        return res;
    }
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    cout << "Сообщение для шифровки: ";
    getline(cin, str);



    Dh_Enc dh_e;
    dh_e.DifHelm_encr(str);
    Dh_Dec dh_d;
    cout << endl;
    dh_d.DifHelm_decr();
}

