#include <iostream>
#include <clocale>
#include "modAlphaCipher1.h"

using namespace std;

/**
 * @brief Прогоняет один тест: шифрует, расшифровывает, сравнивает.
 * @param Text Исходный текст.
 * @param key Ключ.
 * @param destructCipherText Если true — портит первую букву шифротекста,
 *        чтобы проверить, что decrypt кинет ошибку.
 *
 * Результат печатается в консоль: ключ, текст, шифротекст,
 * расшифровка и вердикт Ok/Err.
 */
void check(const wstring& Text, const wstring& key,
           const bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);

        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());

        decryptedText = cipher.decrypt(cipherText);

        wcout << L"key=" << key << endl;
        wcout << Text << endl;
        wcout << cipherText << endl;
        wcout << decryptedText << endl;

        if (Text == decryptedText)
            wcout << L"Ok\n";
        else
            wcout << L"Err\n";
    }
    catch (const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Точка входа: набор тестов из методички.
 *
 * Проверяем нормальные ключи, ключи из строчных букв, пустой ключ,
 * ключ с цифрами и запятыми, текст с мусором и порчу шифротекста.
 */
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");

    check(L"НЕКИТОС", L"КЛЮЧ");
    check(L"НЕКИТОС", L"ПРИМЕР");
    check(L"НЕКИТОС", L"АБВ");

    check(L"НЕКИТОС", L"ключ");
    check(L"НЕКИТОС", L"");
    check(L"НЕКИТОС", L"КЛ1Ч");
    check(L"НЕКИТОС", L"КЛ,Ч");

    check(L"Некит, ос!", L"КЛЮЧ");
    check(L"12345!!!", L"КЛЮЧ");

    check(L"НЕКИТОС", L"КЛЮЧ", true);

    return 0;
}
