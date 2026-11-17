#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

/**
 * @brief Исключение для ошибок шифрования.
 *
 * Отдельный класс нужен, чтобы в main.cpp ловить именно ошибки шифра,
 * а не любые исключения подряд.
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор от std::string.
     * @param what_arg Текст ошибки, который вернёт what().
     */
    explicit cipher_error(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}

    /**
     * @brief Конструктор от C-строки.
     * @param what_arg Текст ошибки.
     */
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};

/**
 * @brief Шифр Виженера для русского алфавита.
 *
 * Каждой букве текста прибавляется буква ключа по модулю длины алфавита.
 * Ключ повторяется, пока не закончится текст. Работаем только с буквами,
 * регистр приводим к верхнему, остальные символы игнорируем.
 */
class modAlphaCipher
{
private:
    /// Алфавит для шифрования. Порядок букв важен — по нему считаются индексы.
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

    /// Соответствие "символ -> индекс", чтобы не искать букву в строке каждый раз.
    std::map<wchar_t, int> alphaNum;

    /// Ключ, переведённый в числа.
    std::vector<int> key;

    /**
     * @brief Строка -> вектор индексов.
     * @param s Входная строка.
     * @return Вектор индексов символов в алфавите.
     */
    std::vector<int> convert(const std::wstring& s);

    /**
     * @brief Вектор индексов -> строка.
     * @param v Вектор индексов.
     * @return Строка символов алфавита.
     */
    std::wstring convert(const std::vector<int>& v);

    /**
     * @brief Проверка и нормализация ключа.
     * @param s Исходный ключ.
     * @return Ключ в верхнем регистре, только из букв.
     * @throw cipher_error Если ключ пуст или содержит не-буквы.
     */
    std::wstring getValidKey(const std::wstring& s);

    /**
     * @brief Очистка открытого текста перед шифрованием.
     * @param s Исходный текст.
     * @return Текст только из заглавных букв.
     * @throw cipher_error Если после очистки не осталось букв.
     */
    std::wstring getValidOpenText(const std::wstring& s);

    /**
     * @brief Проверка шифротекста перед расшифровкой.
     * @param s Шифротекст.
     * @return Тот же текст, если он корректен.
     * @throw cipher_error Если текст пуст или содержит строчные буквы.
     */
    std::wstring getValidCipherText(const std::wstring& s);

public:
    /// Без ключа шифр не имеет смысла — запрещаем.
    modAlphaCipher() = delete;

    /**
     * @brief Создаёт шифр с заданным ключом.
     * @param skey Ключевое слово.
     * @throw cipher_error Если ключ некорректен.
     */
    modAlphaCipher(const std::wstring& skey);

    /**
     * @brief Шифрует открытый текст.
     * @param open_text Текст, который надо зашифровать.
     * @return Шифротекст (заглавные буквы).
     * @throw cipher_error Если открытый текст некорректен.
     */
    std::wstring encrypt(const std::wstring& open_text);

    /**
     * @brief Расшифровывает шифротекст.
     * @param cipher_text Текст, который надо расшифровать.
     * @return Исходный открытый текст.
     * @throw cipher_error Если шифротекст некорректен.
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};
