#include <iostream>

using namespace std;
struct line {
    //int id;      // идетификатор
    int emei;
    string name; // название телефона
    int status;  // статус 0:свободна, 1: занята, 2: удалена
};

class hash_table {
private:
    line *vector; // указатель на начало вектора
    int n;        // максимальный
public:
    hash_table(int size)
    {
        if(size <= 0)
            n = 9;
        else
            n = size;
        vector = new line[n];
        for (int i = 0; i < n; ++i) {
            vector[i].status = 0;
        }
    }
    hash_table() // выделить память. поставить у всех ячеек свободный статус
    {
        n = 9;
        vector = new line[n];
        for (int i = 0; i < n; ++i) {
            vector[i].status = 0;
        }
    }

    ~hash_table() // десктруктор
    {
        delete[] vector; // очистка памяти
    }

    int hash_func_1(int key) {
        return key % n;
    }

    int hash_func_2(int key) {
        return (key + 1) % n;
    }

    bool add(line DB) {

        if(DB.emei < 0 )
        {
            cout << "ERROR: Emei "<< DB.name <<" can't be less then zero." << endl;
            return false;
        } else
        {
            if(search(DB) == 1) // если элемент уже есть
            {
                cout << "ERROR: "<< DB.name <<" have already been added." << endl;
                return false;
            }else
            {
                if(search(DB) == 2) // если emei неоригинален
                {
                    cout << "ERROR: "<< DB.name <<" have unoriginal emei." << endl;
                    return false;
                } else
                {
                    int tmpId = this->hash_func_1(DB.emei);
                    //cout << "tmpId = " << tmpId << endl;
                    int startId = tmpId; // запоминаем начальный интекс чтобы не ходить кругами
                    while (vector[tmpId].status == 1)
                    {
                        tmpId = hash_func_2(tmpId);
                        if (hash_func_2(tmpId) == startId)
                        {
                            break;
                        }
                    }
                    if (vector[tmpId].status == 1)
                    {
                        cout << DB.name << " NOT ADD" << endl;
                        return false;
                    } else
                    {
                        vector[tmpId] = DB; // заносим
                        vector[tmpId].status = 1;
                        //vector[tmpId].id = tmpId;
                        return true;
                    }
                }
            }
        }
    }

    bool del(line DB)
    {
        int tmpId = hash_func_1(DB.emei);
        int startId = tmpId; // запоминаем начальный интекс чтобы не ходить кругами
        while (((DB.emei != vector[tmpId].emei) || (DB.name != vector[tmpId].name)) && (vector[tmpId].status != 0))
        {
            tmpId = hash_func_2(tmpId);
            if (hash_func_2(tmpId) == startId)
            {
                break;
            }
        }
        if((DB.emei == vector[tmpId].emei) && (DB.name == vector[tmpId].name) && (vector[tmpId].status != 3))
        {
            vector[tmpId].status = 3; // статус = удалена
            return true;
        }else
        {
            cout << "ERROR: " << DB.name << " NOT DELL" << endl;
            return false; // удаление не выполнено
        }
    }

    void write() {
        for (int i = 0; i < n; ++i) {
            //cout << "ID = " << vector[i].id << " ";
            cout << "emei = " << vector[i].emei << " ";
            cout << "name = " << vector[i].name << " ";
            cout << "status = " << vector[i].status << endl;
        }
    }

    int search(line DB) // 0, если запись не найдена; 1 если запись найдена; 2 если найдена запись с таким же ключем
    {
        int tmpId = hash_func_1(DB.emei);
        int startId = tmpId; // запоминаем начальный интекс чтобы не ходить кругами
        if((DB.emei == vector[tmpId].emei) and (vector[tmpId].status == 1))
        {
            //cout << " err!! " << " name = " << DB.name << endl;
            return 2; // emei неоригинален
        }
        while (((DB.emei != vector[tmpId].emei) || (DB.name != vector[tmpId].name)) && (vector[tmpId].status != 0))
        {
            tmpId = hash_func_2(tmpId);
            if((DB.emei == vector[tmpId].emei) and (vector[tmpId].status == 1))
            {
                //cout << " err!! " << " name = " << DB.name << endl;
                return 2; // emei неоригинален
            }
            if (hash_func_2(tmpId) == startId)
            {
                break;
            }
        }
        if((DB.emei == vector[tmpId].emei) && (DB.name == vector[tmpId].name) && (vector[tmpId].status != 3))
        {
            return 1; // элемент найден
        }else
        {

            //cout << "DB.emei = " <<DB.emei << " vector[tmpId].emei = " << vector[tmpId].emei << endl;
            return 0; // элемент не найден
        }
    }
};

int main() {

    hash_table a;

    line line1;
    line1.emei = 12;
    line1.name = "galaxy";

//    for (int i=1;i<12;i++) {
//        line1.emei = i * 3;
//        a.add(line1);
//    }
//
//    a.write();
//cout<<endl<<"**************************************"<<endl;
//    for (int i=1;i<8;i++) {
//        line1.emei = i * 3;
//        a.del(line1);
//    }
//     a.write();
//
//    cout<<endl<<"**************************************"<<endl;
//    line1.name = "galaxy";
//
//    for (int i=1;i<12;i++) {
//        line1.emei = (10-i) * 3;
//        a.add(line1);
//    }
//
//    a.write();
    line line2;
    line2.emei = 21;
    line2.name = "htc";

    line line3;
    line3.emei = 30;
    line3.name = "wileyfox";

    line line4;
    line4.emei = 24;
    line4.name = "meizu";

    line line5;
    line5.emei = 25;
    line5.name = "xiaomi";

    line line6;
    line6.emei = 251;
    line6.name = "lg";

    line line7;
    line7.emei = 253;
    line7.name = "sony";

    line line8;
    line8.emei = 253;
    line8.name = "iphone";

    line line9;
    line9.emei = 253;
    line9.name = "philips";

    line testLine;
    testLine.emei = 24;
    testLine.name = "dexp";

    a.add(line1); // пробуем добавить структуру в таблицу
    a.add(line2);
    a.add(line3);

    a.add(line4);
    a.add(line5);

    a.add(line6);
    a.add(line7);
    a.add(line8);
    a.add(line9);
    //a.add(testLine);

    a.write();
//
//    a.del(line1);
//
//    cout << endl;
//
//    a.write();

//    cout << endl;
//
//    a.del(line6);
//    a.write();

//    a.add(line4);
//    a.write();



//   cout << "is line in hash_table? " << a.search(testLine) << endl;

    return 0;
}