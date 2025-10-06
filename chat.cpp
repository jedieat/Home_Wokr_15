#include "chat.h"
#include "iostream"
#include "string.h"

//��� �� ����� 15.4.2 ������������������. ����� ����������� �������� ��������, �� ���������� ������, �� ������ �� �� �� ���������, ����� ��� ������������ � ������-����������

//chat::chat() {
//    data_count = 0;
//}
//
//void chat::reg(char _login[loginlength], char _pass[], int pass_length) {
//    // ��� ���
//    data[data_count++] = authdata(_login, sha1(_pass, pass_length));
//}
//bool chat::login(char _login[loginlength], char _pass[], int pass_length) {
//    // ��� ���
//    // ����� ������� true � ������ ��������� ������
//    int i = 0;
//    for (; i < data_count; i++) {
//        authdata& ad = data[i];
//        if (!strcmp(ad.login, _login)) {
//            break;
//        }
//    }
//    if (i >= data_count) return false;
//
//    uint* digest = sha1(_pass, pass_length);
//
//    bool cmphashes = !memcmp(
//        data[i].pass_sha1_hash,
//        digest,
//        sha1hashlengthbytes);
//    delete[] digest;
//
//    return cmphashes;
//}


Chat::Chat() {
    data_count = 0;
    // �������������� ������ ������� �������
    for (int i = 0; i < SIZE; i++) {
        data[i] = AuthData();
    }
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    if (data_count >= SIZE) {
        std::cout << "Error: Chat is full!" << std::endl;
        return;
    }

    // ���������, �� ��������������� �� ��� ����� �����
    int existing_index = find_index(_login, false);
    if (existing_index != -1) {
        std::cout << "Error: Login already exists!" << std::endl;
        return;
    }

    // ������� ����� ��� �������
    int index = find_index(_login, true);
    if (index == -1) {
        std::cout << "Error: Cannot find place in hash table!" << std::endl;
        return;
    }

    // ������� ����� ������
    data[index] = AuthData(_login, sha1(_pass, pass_length));
    data_count++;
    std::cout << "User '" << _login << "' registered successfully!" << std::endl;
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    int index = find_index(_login, false);
    if (index == -1) {
        return false; // ������������ �� ������
    }

    AuthData& ad = data[index];
    uint* digest = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(
        ad.pass_sha1_hash,
        digest,
        SHA1HASHLENGTHBYTES);

    delete[] digest;
    return cmpHashes;
}