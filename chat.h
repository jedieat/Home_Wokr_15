#pragma once

#include "sha1.h"
#include "string.h"

#define SIZE 32
#define LOGINLENGTH 100

//��� �� ����� 15.4.2 ������������������. ����� ����������� �������� ��������, �� ���������� ������, �� ������ �� �� �� ���������, ����� ��� ������������ � ������-����������
// 
//class chat {
//public:
//    chat();
//    void reg(char _login[loginlength], char _pass[], int pass_length);
//    bool login(char _login[loginlength], char _pass[], int pass_length);
//
//    friend void test(chat& c);
//private:
//    struct authdata {
//        authdata() :
//            login(""),
//            pass_sha1_hash(0) {
//        }
//        ~authdata() {
//            if (pass_sha1_hash != 0)
//                delete[] pass_sha1_hash;
//        }
//        authdata(char _login[loginlength], uint* sh1) {
//            strcpy_s(login, _login);
//            pass_sha1_hash = sh1;
//        }
//        authdata& operator = (const authdata& other) {
//            strcpy_s(login, other.login);
//
//            if (pass_sha1_hash != 0)
//                delete[] pass_sha1_hash;
//            pass_sha1_hash = new uint[sha1hashlengthuints];
//
//            memcpy(pass_sha1_hash, other.pass_sha1_hash, sha1hashlengthbytes);
//
//            return *this;
//        }
//        char login[loginlength];
//        uint* pass_sha1_hash;
//    };
//    authdata data[size];
//    int data_count;
//};


class Chat {
public:
    Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    struct AuthData {
        AuthData() : login(""), pass_sha1_hash(nullptr), isDeleted(false) {}

        AuthData(char _login[LOGINLENGTH], uint* sh1) {
            strcpy_s(login, _login);
            pass_sha1_hash = sh1;
            isDeleted = false;
        }

        ~AuthData() {
            if (pass_sha1_hash != nullptr)
                delete[] pass_sha1_hash;
        }

        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        bool isDeleted;
    };

    // ���-������� ������� ���������
    int hash_function(char login[LOGINLENGTH]) {
        unsigned long long hash = 0;
        for (int i = 0; login[i] != '\0' && i < LOGINLENGTH; i++) {
            hash = hash * 31 + login[i]; // 31 - ������� ����� ��� ������� �������������
        }

        // ����� ���������: h(k) = floor(m * (k * A mod 1))
        const double A = 0.6180339887; // ������� �������
        double fractional = hash * A - (unsigned long long)(hash * A);

        return (int)(SIZE * fractional);
    }

    // ������������ ������������
    int find_index(char login[LOGINLENGTH], bool for_insert = false) {
        int index = hash_function(login);
        int i = 0;

        while (i < SIZE) {
            int current_index = (index + i * i) % SIZE;

            // ���� ��� ������� � ����� ������ ������ ��� ���������
            if (for_insert && (data[current_index].pass_sha1_hash == nullptr || data[current_index].isDeleted)) {
                return current_index;
            }

            // ���� ��� ������ � ����� ������ ����� (�� ���������)
            if (!for_insert && strcmp(data[current_index].login, login) == 0 && !data[current_index].isDeleted) {
                return current_index;
            }

            // ���� ������ ������ (�� ��� �������) - ������ �������� ���
            if (!for_insert && data[current_index].pass_sha1_hash == nullptr) {
                return -1;
            }

            i++;
        }

        return -1; // ������� �����������
    }

    AuthData data[SIZE];
    int data_count;
};
