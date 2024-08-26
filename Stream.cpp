#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

/*
Вариант 8
1. Написать программу преобразования температуры в градусах Цельсия
(например: 15С) в температуру в градусах по Фаренгейту (например: 59F), и
наоборот. 0 градусов по Цельсию соответствует 32 градусам по Фаренгейту.
Изменение температуры на 1 градус по Цельсию соответствует изменению на
1.8 градуса по Фаренгейту. При выводе результата на экран установить
ширину поля 13 символов, точность — 4 цифры, заменить пробелы символом
“/” с помощью функций и манипуляторов. Предусмотреть обработку ошибок.
2. Написать программу копирования файла. В выходном файле сначала
должны быть предложения, состоящие из одного слова, затем те, что состоят
из двух слов, а потом все остальные. Чтение происходит блоками.
Обработать ошибки.
*/

void from_C_to_F(float C) {
    try {
        if (C > 100 || C < -100)
            throw runtime_error("Некоректный ввод температуры!\n");

        float F = (9.0 / 5.0)*C + 32.0;
        cout << "Температура  в градусах Фаренгейту:";
        cout.width(13);
        cout.fill('/');
        cout.setf(std::ios::fixed);
        cout.precision(4);
        cout << F <<endl;

    }
    catch (const runtime_error &ex) {
        cout << ex.what()<<endl;

    }

}

void from_F_to_C(float F) {
    try {
        if (F >212 || F<-148)
            throw runtime_error("Некоректный ввод температуры!\n");
        float C = (5.0 / 9.0) * (F - 32.0);
        cout << "Температура  в градусах Фаренгейту:";
        cout.width(13);
        cout.fill('/');
        cout.setf(std::ios::fixed);
        cout.precision(4);
        cout << C << endl;
    }
    catch (const runtime_error& ex) {
        cout << ex.what() << endl;

    }


}



void add_2_file(string& text, int num_space, ofstream &out ) {

    int num_of_space = 0;
    int pos_of_begin = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ')
            num_of_space++;
        if (text[i] == '.') {
            if (num_of_space == num_space)
                out << text.substr(pos_of_begin, i - pos_of_begin + 1) << " ";

            pos_of_begin = i + 2;
            i++;
            num_of_space = 0;
        }
    }
}


void add_2_file_other(string& text, ofstream& out) {

    int num_of_space = 0;
    int pos_of_begin = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ')
            num_of_space++;
        if (text[i] == '.') {
            if (num_of_space !=0 && num_of_space != 1 )
                out << text.substr(pos_of_begin, i - pos_of_begin + 1) << " ";

            pos_of_begin = i + 2;
            i++;
            num_of_space = 0;
        }
    }

}



int main()
{
    setlocale(LC_ALL, "Russian");

    from_C_to_F(14.0);
    from_C_to_F(0.0);
    from_F_to_C(0);
	from_F_to_C(5000);



    ifstream in("input.txt");
    if (!in)
        cout << "Oшибка чтения файла!\n";



    in.seekg(0, std::ios_base::end);
    const long file_size = in.tellg();
    in.seekg(0);
    char* text = new char[file_size + 1]{};

    const int BUF_SIZE = 10;


    while (!in.eof()) {
        char* buf = new char[BUF_SIZE+1];
        in.get(buf, BUF_SIZE);

        strcat(text,  buf);

        delete[] buf;

    }
    in.close();
    string text_str = text;

    ofstream out("output.txt");
    add_2_file(text_str, 0, out);
    out.close();

    ofstream out1("output.txt", ios::app);
    add_2_file(text_str, 1, out1);
    out1.close();

    ofstream out2("output.txt", ios::app);
    add_2_file_other(text_str, out2);
    out2.close();



    return 0;
}

