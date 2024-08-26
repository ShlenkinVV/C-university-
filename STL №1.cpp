#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include <ctime>
#include <list>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Money {                               //пользовательский тип данных
    int cent;
public:
    Money() { val = 0; }
    Money(float v) { val = v; }
    operator float() { return val; }
    Money operator = (float v) { val = v; return *this; }
    Money operator -= (Money& m) { val -= float(m.val); return *this; }
    float operator -=(float v) { return val -= v; }
    float getVal() const { return val; }

    friend std::ostream& operator <<(std::ostream& strm, Money& m) {
        strm << "Money = " << m.cent/100 << " $ " <<m.cent % 100 << "cent\n";
        return strm;
    }
    friend std::ostream& operator <<(std::ostream& strm, const Money& m) {
        cout << "Money = " << m.val << " $ \n";
        return strm;
    }
   


};

bool operator<(const Money& l, const Money& r) {
    if (l.getVal() < r.getVal())
        return true;
    else return false;
};





template <typename T_any_cont>                         //шаблонный класс
class myCont {
public:
    typedef T_any_cont T_usr_cont;
private:
    T_usr_cont cont;
public:
    myCont(size_t n_el) { cont = ::create_cont<T_usr_cont>(n_el); }

    void print_cont() { ::print_cont<T_usr_cont>(cont); }

    void find_value(typename T_usr_cont::value_type val, int position) { ::find_value<T_usr_cont>(cont, val, position); }

    void max_minus_min() { ::max_minus_min<T_usr_cont>(cont); }

    void delete_key(typename T_usr_cont::value_type key) { ::delete_key<T_usr_cont>(cont, key); }

};


typedef list<double> T_cont;
typedef list<Money> T_cont_Money;



template <typename T>
T create_cont(size_t n_el) {                   // функция создания контейнера
    T res;
    for (size_t i = 1; i <= n_el; i++) {
        typename T::value_type el = i*1000 + i * 10.0;
        res.push_back(el);
    }
    return res;
}



template <typename T>
void print_cont(T& c) {
    typename T::iterator it;
    for (it = c.begin(); it != c.end(); ++it)
        cout << " " << *it;
    cout << endl;
}

template <typename T>
void find_value(T& c, typename T::value_type val, int position) {
    cout << "\n Функция нахождения элемента и вставки его на заданную позицию\n";
    typename T::iterator it;
    typename T::iterator  it2 = c.begin();
    bool flag = false;
    int i = 0;
    for (it = c.begin(); it != c.end(); ++it)
        if (*it == val) {
            flag = true;
            while (i != position) {
                i++;
                it2++;
            }
            c.insert(it2, val);
            break;
        }
    if (!flag)
        cout << " Элемент не найден\n";

}

template<typename T>
typename T::value_type get_min(T& c) {
    typename T::iterator it;
    typename T::value_type res = *c.begin();
    for (it = c.begin(); it != c.end(); ++it)
        if (res > *it) // сумма
            res = *it;
    cout << " Min: " << res << endl;
    return res;
}

template<typename T>
typename T::value_type get_max(T& c) {
    typename T::iterator it;
    typename T::value_type res = *c.begin();
    for (it = c.begin(); it != c.end(); ++it)
        if (res < *it) // сумма
            res = *it;
    cout << " Max: " << res << endl;
    return res;
}

template<typename T>
void max_minus_min(T& c) {
    cout << "\n Функция вичитания из каждого элемента разность маскимального и минимального\n";
    typename T::iterator it;
    typename T::value_type min = get_min(c);
    typename T::value_type max = get_max(c);
    for (it = c.begin(); it != c.end(); ++it) {
        *it -= max - min;
    }
}

template<typename T>
void delete_key(T& c, typename T::value_type key) {
    cout << "\n Функия удаления элемента\n";
    typename T::iterator it;
    for (it = c.begin(); it != c.end(); ++it) {
        if (*it == key)
            it = c.erase(it);
    }

}

typedef std::vector<Money> T_v;
//typedef std::priority_queue<T_v::value_type, T_v> T_adapt;          //создали контейнер
typedef std::priority_queue<T_v::value_type, T_v, less <T_v::value_type>> T_adapt;


template <typename T_adpt>
void print(T_adpt ad)
{
    while (!ad.empty())
    {

        std::cout << ad.top() << " ";
        ad.pop();
    }
    cout << '\n';
}



template <class T_cnt, class T_adpt>
T_adpt convert_cont_2_adapt(T_cnt cnt)
{
    T_adpt ad;
    while (!cnt.empty())
    {
        ad.push(cnt.back());
        cnt.pop_back();
    }
    return ad;
}


template <class T_cnt, class T_adpt>
T_cnt convert_adapt_2_cont(T_adpt ad)
{
    T_cnt res;
    while (!ad.empty())
    {
        res.insert(res.begin(), ad.top());
        ad.pop();
    }
    return res;
}

template <typename T>
class my_adapter {                                                  //Параметризованный класс
public:
    typedef std::priority_queue<typename T::value_type, T> T_usr_ad;
    typedef T T_c;
private:
    T_usr_ad ad;
public:

    my_adapter(size_t n_el) : ad(::create_cont<T_c>(n_el)) { ; }

    my_adapter(const T_usr_ad& v) :ad(v) { ; }

    my_adapter& operator=(const T_usr_ad& v) { ad = v; return *this; }

    void print() {
        T_c cont = convert_adapt_2_cont <T_c, T_usr_ad>(ad);
        print_cont<T_c>(cont);
    }

    void find_value(typename T_c::value_type val, int position) {
        T_c cont = convert_adapt_2_cont<T_c, T_usr_ad>(ad);
        ::find_value(cont, val, position);
        ad = convert_cont_2_adapt<T_c, T_usr_ad>(cont);
    }

    void delete_key(typename T_c::value_type key) {
        T_c cont = convert_adapt_2_cont<T_c, T_usr_ad>(ad);
        ::delete_key<T_c>(cont, key);
        ad = convert_cont_2_adapt<T_c, T_usr_ad>(cont);
    }
    void max_minus_min() {
        T_c cont = convert_adapt_2_cont<T_c, T_usr_ad>(ad);
        ::max_minus_min<T_c>(cont);
        ad = convert_cont_2_adapt<T_c, T_usr_ad>(cont);
    }

};

int main() {
    setlocale(LC_ALL, "ru");
    T_cont cont = create_cont<T_cont>(10);
    cout << "Список double\n";
    print_cont(cont);
    find_value(cont, 6.6, 1);
    print_cont(cont);
    delete_key(cont, 8.8);
    print_cont(cont);

    max_minus_min(cont);
    print_cont(cont);
    cout << "\n //////////////////////////////////////////////////////// \n\n";
    cout << " Параметризированный класс myCont(double)\n";
    myCont<std::vector<double>> mc(10);

    mc.print_cont();
    mc.find_value(6.6, 1);
    mc.print_cont();
    mc.delete_key(8.8);
    mc.print_cont();
    mc.max_minus_min();
    mc.print_cont();

    cout << "\n //////////////////////////////////////////////////////// \n\n";
    cout << " Параметризированный класс myCont с пользовательским типом (Money)\n";
    myCont<std::vector<Money>> mc1(10);
    mc1.print_cont();
    mc1.find_value(6.6, 1);
    mc1.print_cont();
    mc1.delete_key(8.8);
    mc1.print_cont();
    mc1.max_minus_min();
    mc1.print_cont();



    ////////////////////////////////////////////////////////////////


    cout << "\n //////////////////////////////////////////////////////// \n\n";

    T_v myVector = create_cont<T_v>(10);
    T_adapt adpt = convert_cont_2_adapt<T_v, T_adapt>(myVector);
    cout << "\nВектор пользовотельского типа \n";
    print_cont<T_v>(myVector);
    cout << "\nАдаптер (очередь с приоритетом)\n";
    print<T_adapt>(adpt);

    cout << "\n Пользовательский класс адаптера\n";

    my_adapter<T_v> adapter(adpt);
    adapter.print();
    adapter.find_value(6.6, 1);
    adapter.print();
    adapter.delete_key(8.8);
    adapter.print();
    adapter.max_minus_min();
    adapter.print();
    return 0;
}

