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

    void gen_g(long int& g) {
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(2, p - 1);
        g = dist(gen);
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

class RSA_Enc {
public:
    int64_t p;                                       
    int64_t q;                                       
    int64_t e;                                       
    void rsa_e(string text) {

        cout << "Зашифрованное сообщение: ";

        rsa_alg();
        enc(text);

        cout << "\nКлючи для расшифровки: d = " << d << ", n = " << n << endl;
        dec();
    }
private:  

    int64_t n;                                       
    int64_t f;
    int64_t d;
    vector<int64_t> vec;

    void dec() {
        for (auto i : vec) {
            int64_t m = ost(i, d, n);
            cout << char(m);
        }
    }

    void enc(string text) {
        for (auto i : text) {
            int64_t m = int(i);
            int64_t c = ost(m, e, n);
            cout << c << " ";
            vec.push_back(c);
        }
    }

    void rsa_alg() {
        p = gen_prost();
        q = gen_prost();
        n = p * q;
        f = (p - 1) * (q - 1);
        e = vzaim_prost(f);
        d = obrat(e, f);
    }

    int64_t gen_prost() {
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(100,500);
        while (true) {
            int64_t p = dist(gen);
            int64_t i;
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

    int64_t obrat(int64_t b, int64_t a) {
        int64_t x = 1, y = 0, x1 = 0, y1 = 1, x2 = 0, y2 = 0, q = 0, r = 1, a1;
        a1 = a;

        while (r != 0) {
            q = a / b;
            r = a % b;
            x2 = x - q * x1;
            y2 = y - q * y1;
            x = x1;
            y = y1;
            x1 = x2;
            y1 = y2;
            a = b;
            b = r;

        }
        if (y < 0) {
            y = y + a1;
        }
  
        return y;
    }

    int64_t nod(int64_t a, int64_t b) {
        while (b != 0) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    int64_t vzaim_prost(int64_t p) {
        random_device rd;
        ranlux24_base gen(rd());
        uniform_int_distribution<> dist(2, p - 1);
        while (true) {
            int64_t k = dist(gen);
            if (nod(k, p - 1) == 1) {
                return k;
            }
        }
    }

    int64_t ost(int64_t a0, int64_t x0, int64_t p0) {
        int64_t a = a0, x = x0, q = 1, p = p0;
        while (x > 0) {
            if (x % 2 == 0) {
                x /= 2;
                a = (a * a) % p;
            }
            else {
                x--;
                q = (a * q) % p;
            }
        }
        return q;
    }
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    cout << "Сообщение для шифровки: ";
    getline(cin, str);


    RSA_Enc rsa_e;
    rsa_e.rsa_e(str);








    //El_Gamal_Enc el_enc;

    //el_enc.El_Gamal_e(str);

    //El_Gamal_Dec el_dec;

    //el_dec.El_Gamal_d();













    //Dh_Enc dh_e;
    //dh_e.DifHelm_encr(str);
    //
    //cout << endl;

    //Dh_Dec dh_d;
    //dh_d.DifHelm_decr();
}

