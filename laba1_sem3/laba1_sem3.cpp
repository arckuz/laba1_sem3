#include "Header.h"

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
        string res = "";
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
class El_Gamal_Enc {
public:
    long int p;
    long int g;
    string message;

    void El_Gamal_e(string text) {
        long int Y;
        p = gen_p(p);
        gen_g(g);
        cout << "Введите сессионный ключ 1 < x < "<<p-1<<" : ";
        cin >> x;
        message = text;
        

        Y = step(g, x, p); 

        encryption(p, g, Y, message, encoded_message);
        cout << endl;
        cout << "Ключи для дешифровки: p = " << p << " x = " << x << endl;
        //decryption(p, x, encoded_message);
    }
private:
    long int x;
    vector<pair<long int, long int>> encoded_message;

    int gen_p(long int p) {
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(1000, 40000);
        while (true) {
            int p = dist(gen);
            int i;
            for (i = 2; i < p / 2; i++) {
                if (p % i == 0) {
                    break;
                }
            }
            if (i == p / 2) {
                return p;
            }
        }
    }
    void gen_g(long int& g) {
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(2, p-1);
        g = dist(gen);
    }
    int step(int a, long int x, int p) {
        int y;
        y = x % (p - 1);
        int t, t0;
        t = 0;
        t0 = a % p;
        for (int k = 0; k < y; ++k) {
            t = a % p;
            a = t * t0;
        }
        return t;
    }
    int step_with_numb(int Y, int k, int M, int p) {
        int q, q0;
        q = Y % p;
        q0 = q;
        for (int i = 1; i < k; i++) {
            q = (q * q0) % p;
        }
        q = (q * M) % p;
        return q;
    }
    int nod(int a, int b) {
        while (b != 0) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    int vzaim_prost(int p) {
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(2, p - 1);
        while (true) {
            long int k = dist(gen);
            if (nod(k, p - 1) == 1) {
                return k;
            }
        }
    }
    void encryption(long int p, long int g, long int Y, string message, vector<pair<long int, long int>>& encoded_message) {
        for (auto i : message) {
            int M = int(i);
            long int k = vzaim_prost(p);//случайное взаимно простое
            long int A = step(g, k, p);
            long int B = step_with_numb(Y, k, M, p);
            cout << A << " " << B << " ";
            encoded_message.push_back(make_pair(A, B));
        }
        cout << endl;
    }
};
class El_Gamal_Dec {
public:
    long int p;
    string text;

    void El_Gamal_d() {
        cout << "Введите p: ";
        cin >> p;
        cout << "Введите секретный ключ x: ";
        cin >> x;
        cin.get();
        cout << "Введите сообщение для расшифровки: ";
        getline(cin, text);
        text += ' ';
        preobr(text);
        for (auto i : encoded_message) {
            int A = i.first;
            int B = i.second;
            int M1 = step_with_numb(A, p - 1 - x, B, p);
            cout << char(M1);
        }
    }
private:
    long int x;
    vector<pair<long int, long int>> encoded_message;

    int step_with_numb(int Y, int k, int M, int p) {
        int q, q0;
        q = Y % p;
        q0 = q;
        for (int i = 1; i < k; i++) {
            q = (q * q0) % p;
        }
        q = (q * M) % p;
        return q;
    }
    void preobr(string str) {
        string a="", b="";
        bool first_space = false, second_space=false;
        for (auto i : str) {
            if (i != ' ' && !first_space && !second_space) {
                a += i;
            }
            else if (i != ' ' && first_space && !second_space) {
                b += i;
            }
            else if (i == ' ' && !first_space && !second_space) {
                first_space = true;
                continue;
            }
            else if (i == ' ' && first_space && !second_space) {
                encoded_message.push_back(make_pair(stoi(a), stoi(b)));
                a = "";
                b = "";
                first_space = false;
            }
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    cout << "Сообщение для шифровки: ";
    getline(cin, str);

    El_Gamal_Enc el_enc;

    el_enc.El_Gamal_e(str);

    El_Gamal_Dec el_dec;

    el_dec.El_Gamal_d();













    //Dh_Enc dh_e;
    //dh_e.DifHelm_encr(str);
    //
    //cout << endl;

    //Dh_Dec dh_d;
    //dh_d.DifHelm_decr();
}

