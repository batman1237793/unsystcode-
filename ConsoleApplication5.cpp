#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
// Функция для получения остатка от деления
vector<int> getRemainder(const vector<int>& data, const vector<int>& gx) {
    int n = data.size();
    int m = gx.size();
    vector<int> remainder(m - 1, 0);

    for (int i = 0; i < n; i++) {
        if (remainder[0] == 1) {
            for (int j = 0; j < m - 2; j++) {
                remainder[j] = remainder[j + 1] ^ gx[j + 1];
            }
        }
        else {
            for (int j = 0; j < m - 2; j++) {
                remainder[j] = remainder[j + 1];
            }
        }
        remainder[m - 2] = data[i];
    }

    return remainder;
}

// Функция для кодирования данных
vector<int> encodeData(const vector<int>& data, const vector<int>& gx) {
    int n = data.size();
    int m = gx.size();
    vector<int> encodedData(n + m - 1, 0);

    for (int i = 0; i < n; i++) {
        encodedData[i] = data[i];
    }

    vector<int> remainder = getRemainder(encodedData, gx);

    for (int i = 0; i < m - 1; i++) {
        encodedData[n + i] = remainder[i];
    }

    return encodedData;
}

// Функция для декодирования данных
vector<int> decodeData(const vector<int>& encodedData, const vector<int>& gx) {
    vector<int> remainder = getRemainder(encodedData, gx);

    // Проверка на наличие ошибок
    for (int i = 0; i < remainder.size(); i++) {
        if (remainder[i] != 0) {
            cout << "Ошибка при передаче данных!" << endl;
            return {};
        }
    }

    int n = encodedData.size() - gx.size() + 1;
    vector<int> decodedData(n, 0);
    for (int i = 0; i < n; i++) {
        decodedData[i] = encodedData[i];
    }

    return decodedData;
}
int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> encodedData;
    vector<int> decodedData;
    int n = 15;
    vector<int> gx = { 1, 1, 0, 1, 0, 0, 0, 1 }; // Полином g(x)
    vector<int> data(n, 0);

    int choice;
    do {
        cout << "\nВыберите операцию:\n";
        cout << "1. Ввести данные\n";
        cout << "2. Кодировать данные\n";
        cout << "3. Декодировать данные\n";
        cout << "4. Добавить ошибку\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Данные: ";
            for (int i = 0; i < n; i++) {
                data[i] = rand() % 2;
                cout << data[i] << " ";
            }
            cout << endl;
            break;
        }
        case 2: {
            if (data.empty()) {
                cout << "Сначала введите данные!\n";
                break;
            }
            encodedData = encodeData(data, gx);

            cout << "Закодированные данные: ";
            for (int i = 0; i < encodedData.size(); i++) {
                cout << encodedData[i] << " ";
            }
            cout << endl;
            break;
        }
        case 3: {
            if (encodedData.empty()) {
                cout << "Сначала закодируйте данные!\n";
                break;
            }
            decodedData = decodeData(encodedData, gx);
            n = 15;

            // Проверяем, был ли пустой вектор возвращен из decodeData
            if (!decodedData.empty()) {
                cout << "Декодированные данные: ";
                for (int i = 0; i < decodedData.size(); i++) {
                    cout << decodedData[i] << " ";
                }
                cout << endl;
            }
            break;
        }
        
        case 4: {
            if (encodedData.empty()) {
                cout << "Сначала закодируйте данные!\n";
                break;
            }
            int errorIndex;
            cout << "Введите индекс бита для изменения: ";
            cin >> errorIndex;

            if (errorIndex >= 0 && errorIndex < encodedData.size()) {
                encodedData[errorIndex] = 1 - encodedData[errorIndex];
                cout << "Ошибка добавлена!\n";
                cout << "Закодированные данные с ошибками: \n";
                for (int i = 0; i < encodedData.size(); i++) {
                    cout << encodedData[i];
                }
            }

            else {
                cout << "Неверный индекс!\n";
            }
            break;
        }
        case 0:
            cout << "Выход...\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}