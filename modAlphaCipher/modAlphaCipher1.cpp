#include "modAlphaCipher1.h"
#include <cwctype>

/**
 * @brief Конструктор: заполняет мапу и сразу проверяет ключ.
 *
 * Мапа заполняется один раз, чтобы convert() потом просто
 * брал готовые индексы.
 */
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

/**
 * @brief Шифрует текст: (буква + ключ) по модулю длины алфавита.
 *
 * Ключ "зацикливаем" через i % key.size(), чтобы он повторялся.
 */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Расшифровывает текст: (буква - ключ) по модулю длины алфавита.
 *
 * Прибавляем размер алфавита, чтобы не получить отрицательное число
 * при вычитании.
 */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Переводит строку в вектор индексов.
 */
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

/**
 * @brief Переводит вектор индексов в строку.
 */
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

/**
 * @brief Проверка ключа.
 *
 * Ключ не должен быть пустым и должен состоять только из букв.
 * Строчные буквы приводим к заглавным, чтобы "ключ" и "КЛЮЧ"
 * давали одинаковый результат.
 */
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty key");

    std::wstring tmp(s);
    for (auto& c : tmp) {
        if (!iswalpha(c))
            throw cipher_error("Invalid key");
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}

/**
 * @brief Очистка открытого текста.
 *
 * Оставляем только буквы, строчные делаем заглавными.
 * Всё остальное (пробелы, цифры, знаки) просто игнорируем.
 */
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

/**
 * @brief Проверка шифротекста.
 *
 * В нормальном шифротексте только заглавные буквы.
 * Если встретили что-то другое — значит, текст испорчен.
 */
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");

    for (auto c : s) {
        if (!iswupper(c))
            throw cipher_error("Invalid cipher text");
    }
    return s;
}
