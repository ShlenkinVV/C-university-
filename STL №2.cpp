#include <iostream>
#include <map>
#include <utility>     
#include <algorithm>
#include <vector>
#include <list>
#include <set>




/*Вариант 8

 1)    список                                   Пункт 3 Задача Х(Х = 1...3 ) Найти элемент с заданным ключом и
                                                добавить его на заданную позицию контейнера.

 2)    Не сортированный                         Пункт 4 Задача Х(Х = 1...3 ) Найти элемент с заданным ключом и
     ассоциативный контейнер –                  удалить его из контейнера.
        множество.                                            
                                      
 3)   Ассоциативный контейнер –                 Пункт 5 Задача Х(Х = 1...3 ) Найти разницу между максимальным и
      словарь с дубликатами.                    минимальным элементами контейнера и вычесть ее из каждого
                                                элемента контейнера.



*/
using namespace std;



class Money {                               //пользовательский тип данных
    mutable int cent;
 
public:
    Money() { cent = 0;  }
    Money(float v) { cent = v; }
    Money(const Money& m) :cent(m.cent) { ; }
    operator float() const { return cent; }
    Money operator =(const Money& m) { cent = m.cent; return *this; }
   // Money operator = (float v) { cent = v; return *this; }
    Money operator = (float v) const { cent=v; return *this;};
   // float operator -=(float v) { return cent -= v; }
    float operator -=(float v) const { return cent -= v; }
    Money operator -(const Money& m) { return cent -= m.cent; }
    float getVal() const { return cent; }

   /* friend std::ostream& operator <<(std::ostream& strm, Money& m) {
        strm << "Money = " << m.cent / 100 << " " << m.cent % 100  ;
        return strm;
    }*/
    friend std::ostream& operator <<(std::ostream& strm, const Money& m) {
        cout << "Money = " << m.cent / 100 << " " << m.cent % 100 ;
        return strm;
    }
 
   // friend bool operator ==(const Money& m, const Money& c) { return m.cent == c.cent; }

    bool operator ==(const Money& m) { return m.getVal() == cent; }
  
 };

bool operator<(const Money& l, const Money& r) {
    if (l.getVal() < r.getVal())
        return true;
    else return false;
};


typedef std::list<Money> T_cont_list;
typedef std::set<Money> T_cont_set;
typedef std::multimap<Money, string> T_cont_mul_map;
typedef std::vector<Money> T_vec;

template < class T >
typename T::iterator get_iterator_by_pos(int pos, T& cont)
{
    typename T::iterator res = cont.end();
    typename T::iterator it;
    int cnt = 0;
    for (it = cont.begin(); it != cont.end(); ++it)
    {
        if (cnt == pos) res = it;
        cnt++;
    }
    return res;
}


/*template <typename T>
T create_cont(size_t n_el) {                   // функция создания контейнера
    T res;
    for (size_t i = 1; i <= n_el; i++) {
        typename T::value_type el = rand() % 90000 + 1000;
        res.push_back(el);
    }
    return res;
}*/

template <typename T>
T create_cont(int n_el) {  
    T res;
    for (int i = 0; i < n_el; i++) {
        typename T::value_type el = rand() % 90000 + 1000;
        res.insert(get_iterator_by_pos<T>(i, res), el);
    }
    return res;
}



template <typename T>
void print_cont(T& c) {
    typename T::iterator it;
    for (it = c.begin(); it != c.end(); ++it)
        cout << " " << *it<<endl;
    cout << endl;
}

template <typename T>
void print_cont_el(const T& c) {
    cout << c<<endl;
}



template < class T > 
T create_assoc_cont(int n_el)
{
    T res;
    string currency;
    for (int i = 0; i < n_el; i++)
    {
        int cur = rand() % 3;
        switch (cur) {
        case 0:
            currency = "RUB";
            break;
        case 1:
            currency = "USD";
            break;
        case 2:
            currency = "EUR";
            break;
        }
        typename T::value_type el( rand() % 90000 + 1000, currency);   // using make_pair (move)
        res.insert(el);
    }
    return res;
}

template < typename T > 
void print_pair(const T& pair)
{
    cout << pair.first << " " << pair.second << '\n';
}

template < typename T >
void print_acont(T& cont)
{
    typename T::iterator it;
    for (it = cont.begin(); it != cont.end(); ++it) { 
        print_pair<typename T::value_type>(*it); }
    cout << '\n';
}





template < typename T > 
class c_comp_pair {
    T v;
public:
    c_comp_pair(T ref) :v(ref) { ; }
    bool operator()(T val) { 
        return (val.first.getVal() == v.first.getVal()); } 
  
};


template < class T > 
class c_comp_value {
    T v;
public:
    c_comp_value(T ref) :v(ref) { ; }
    bool operator()(T val) { 
        return (val.getVal() == v.getVal()); }  
 
};




template <typename T_cont, typename T_obj>
void find_el_list(T_cont& c, T_obj obj, int position) {
    c_comp_value<typename T_cont::value_type> compObjList(obj);
    typename T_cont::iterator it;
    it = find_if(c.begin(), c.end(), compObjList);
    if (it != c.end()) {
        print_cont_el<T_cont::value_type>(*it);
        cout << "Элемент найден\n";
        c.insert(get_iterator_by_pos<T_cont>(position, c), *it);
    }
    else {
        std::cout << "Элемент не найден\n";
    }
}


template <typename T_cont, typename T_obj>
void find_el_acont(T_cont& c, T_obj obj, int position) {
    c_comp_pair<typename T_cont::value_type> compObjList(obj);
    typename T_cont::iterator it;
    it = find_if(c.begin(), c.end(), compObjList);
    if (it != c.end()) {
        print_pair<T_cont::value_type>(*it);
        cout << "Элемент найден\n";
        c.insert(get_iterator_by_pos<T_cont>(position, c), *it);
    }
    else {
        std::cout << "Элемент не найден\n";
    }
}



template < class T >
class max_minus_min{
    T v;
public:
    max_minus_min(const T ref) :v(ref) { ; }
    float max = *max_element(v.begin(), v.end());
    float min = *min_element(v.begin(), v.end());
    float val = max - min;
    void operator()(const Money& m) {m-=val; }  
};

template<typename T_cont>
class max_minus_min_map {
    typename T_cont::first_type cont;
public:
     max_minus_min_map(typename T_cont::first_type &c) :cont (c) { ; }
   
     bool operator ()(T_cont& c) { return (c.first -= cont); }
};


int main()
{
    setlocale(LC_ALL, "ru");
    T_cont_list cont_list = create_cont<T_cont_list>(10);
 
    Money el_2_find(1041);
    find_el_list<T_cont_list, Money>(cont_list, el_2_find, 4);
    print_cont<T_cont_list>(cont_list);


    Money el_2_del(20169);
    cout << "Фунция удаления элемента(201 69)\n";
    remove(cont_list.begin(), cont_list.end(), el_2_del);
    print_cont<T_cont_list>(cont_list);


    max_minus_min<T_cont_list> mObj(cont_list);
    cout << "Фунция вычитания разности максимального и минимального значения\n";
    for_each(cont_list.begin(), cont_list.end(), mObj);
    print_cont<T_cont_list>(cont_list);
  
 
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";

    T_cont_set cont_set = create_cont<T_cont_set>(10);
    print_cont<T_cont_set>(cont_set);

   
    cout << "Функция нахождения элемента\n";
    Money el_2_find_2(3995);
    find_el_list<T_cont_set, Money>(cont_set, el_2_find_2, 4);
    print_cont<T_cont_set>(cont_set);


    cout << "Функция удаления элемента(129 42)\n";
    Money el_2_del_2(12942);
    remove(cont_set.begin(), cont_set.end(), el_2_del_2);
    print_cont<T_cont_set>(cont_set);

    
    cout << "Функция вычитания разности max и min\n";
    max_minus_min<T_cont_set> mObj2(cont_set);
    for_each(cont_set.begin(), cont_set.end(), mObj2);
    print_cont<T_cont_set>(cont_set);
  
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";

    T_cont_mul_map cont_map = create_assoc_cont<T_cont_mul_map>(10);
    print_acont<T_cont_mul_map>(cont_map);

    T_cont_mul_map::value_type el_2_find_3(19716, "RUB");
    find_el_acont<T_cont_mul_map>(cont_map, el_2_find_3, 8);
    print_acont<T_cont_mul_map>(cont_map);

    cout << "Функция удаления элемента (133 82 USD)\n";
    T_cont_mul_map::iterator it;

    T_cont_mul_map res;
    T_cont_mul_map::value_type el_2_del_3(13382, "USD");
    c_comp_pair<T_cont_mul_map::value_type> compObj(el_2_del_3);

    for (it = cont_map.begin(); it != cont_map.end(); ++it) {
        if (!compObj(*it)) 
            res.insert(*it);
    }
    cont_map = res;

    //remove(cont_map.begin(), cont_map.end(), compObj);
    print_acont<T_cont_mul_map>(cont_map);


    cout << "Функция вычитания разности max и min\n";
    T_vec vec;
    for (it = cont_map.begin(); it != cont_map.end(); ++it) {
        vec.push_back(it->first);
    }
    T_cont_mul_map::value_type::first_type range = *max_element(vec.begin(), vec.end()) - *min_element(vec.begin(), vec.end());
    cout << "Разность: " << range << endl;
    max_minus_min_map<T_cont_mul_map::value_type> mapObj(range);
    for_each(cont_map.begin(), cont_map.end(), mapObj);
    print_acont<T_cont_mul_map>(cont_map);


    return 0;
}

