#include "chat.h"
#include <iostream>
#include <cstring>


using namespace std;





int main() {
    setlocale(LC_ALL, ""); // ��� system("chcp 1251") ������ ���������� �� �������; 
    Chat chat;
    int choice;
    char login[LOGINLENGTH];
    char password[100];

    cout << "Hi!" << endl;

    while (true) {

        cout << "1. �����������" << endl;
        cout << "2. �����" << endl;

        cin >> choice;
        cin.ignore(); // ������� ������ �����

        switch (choice) {
        case 1: {
            // �����������
            cout << "������� ����� (�������� " << LOGINLENGTH - 1 << " chars): ";
            cin.getline(login, LOGINLENGTH);

            cout << "������� ������: ";
            cin.getline(password, 100);

            chat.reg(login, password, strlen(password));
            cout << "����������� ���������" << endl << endl;
            break;
        }

        case 2: {
            // ����
            cout << "������� �����: ";
            cin.getline(login, LOGINLENGTH);

            cout << "������� ������: ";
            cin.getline(password, 100);

            if (chat.login(login, password, strlen(password))) {
                cout << "����� ��������, " << login << "!" << endl << endl;
            }
            else {
                cout << "������������ ��� ������������ ��� ������" << endl << endl;
            }
            break;
        }

        case 3: {
            cout << "�����" << endl;
            return 0;
        }

        default: {
            cout << "������������ �����." << endl << endl;
            break;
        }
        }
    }

    return 0;
}