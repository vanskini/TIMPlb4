#include <iostream>
#include <clocale>
#include <string>
#include "TableCipher.h"

using namespace std;

/**
 * @brief Прогоняет один тест табличного шифра.
 * @param text Текст.
 * @param key Ключ (число столбцов).
 * @param destructCipherText Если true — портит первую букву шифротекста,
 *        чтобы проверить обработку ошибки при расшифровке.
 *
 * Печатает ключ, исходный текст, шифротекст, расшифровку и длины строк.
 */
static void check(const wstring& text, int key, const bool destructCipherText = false)
{
    try {
        TableCipher cipher(key);

        wstring cipherText = cipher.encrypt(text);

        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());

        const wstring decryptedText = cipher.decrypt(cipherText);

        wcout << L"ключ              : " << key            << L'\n';
        wcout << L"текст             : " << text           << L'\n';
        wcout << L"зашифрованный     : " << cipherText     << L'\n';
        wcout << L"расшифрованный    : " << decryptedText  << L'\n';
        wcout << L"длины (in/out)    : " << text.size() << L" / " << decryptedText.size() << L'\n';

        if (text == decryptedText)
            wcout << L"Ok\n";
        else
            wcout << L"Err\n";
    }
    catch (const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Точка входа: тесты из методички.
 */
int main()
{
    setlocale(LC_ALL, "");

    check(L"СИКССЕВЕН", 3);
    check(L"ПАСПОРТ",   4);
    check(L"НЕКТОТОС",  2);

    check(L"сикссевен", 3);
    check(L"Сиксс, севен!", 3);
    check(L"12345!!!", 3);
    check(L"", 3);
    check(L"СИКССЕВЕН", 0);
    check(L"СИКССЕВЕН", -1);
    check(L"СИКССЕВЕН", 3, true);

    return 0;
}
