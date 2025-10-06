#include "chat.h"
#include <iostream>
#include <cstring>


using namespace std;





int main() {
    setlocale(LC_ALL, ""); // или system("chcp 1251") меняем кракозябры на русский; 
    Chat chat;
    int choice;
    char login[LOGINLENGTH];
    char password[100];

    cout << "Hi!" << endl;

    while (true) {

        cout << "1. Регистрация" << endl;
        cout << "2. Логин" << endl;

        cin >> choice;
        cin.ignore(); // очистка буфера ввода

        switch (choice) {
        case 1: {
            // Регистрация
            cout << "Введите логин (символов " << LOGINLENGTH - 1 << " chars): ";
            cin.getline(login, LOGINLENGTH);

            cout << "Введите пароль: ";
            cin.getline(password, 100);

            chat.reg(login, password, strlen(password));
            cout << "Регистрация выполнена" << endl << endl;
            break;
        }

        case 2: {
            // Вход
            cout << "Введите логин: ";
            cin.getline(login, LOGINLENGTH);

            cout << "Введите Пароль: ";
            cin.getline(password, 100);

            if (chat.login(login, password, strlen(password))) {
                cout << "Логин выполнен, " << login << "!" << endl << endl;
            }
            else {
                cout << "Неправильное имя пользователя или пароль" << endl << endl;
            }
            break;
        }

        case 3: {
            cout << "Конец" << endl;
            return 0;
        }

        default: {
            cout << "Недопустимая опция." << endl << endl;
            break;
        }
        }
    }

    return 0;
}