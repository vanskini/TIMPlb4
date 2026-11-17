#pragma once
#include <string>
#include <stdexcept>

/**
 * @brief Исключение для ошибок табличного шифра.
 *
 * Своё исключение, чтобы ловить именно ошибки шифрования,
 * а не всё подряд.
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор от std::string.
     * @param what_arg Текст ошибки.
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
 * @brief Табличный шифр (маршрутная перестановка).
 *
 * Текст пишется в таблицу по строкам, читается по столбцам справа налево.
 * Ключ — число столбцов в таблице. При расшифровке всё делается наоборот.
 */
class TableCipher
{
private:
    /// Число столбцов в таблице (ключ).
    int columns;

    /**
     * @brief Проверка ключа.
     * @param key Число столбцов.
     * @return Пустую строку (для совместимости с другими getValid*).
     * @throw cipher_error Если ключ меньше 1 или больше 1000.
     *
     * Верхняя граница — чтобы таблица не заняла слишком много памяти.
     */
    std::wstring getValidKey(int key) const;

    /**
     * @brief Очистка открытого текста перед шифрованием.
     * @param s Исходный текст.
     * @return Текст только из заглавных букв.
     * @throw cipher_error Если после очистки не осталось букв.
     */
    std::wstring getValidOpenText(const std::wstring& s) const;

    /**
     * @brief Проверка шифротекста перед расшифровкой.
     * @param s Шифротекст.
     * @return Тот же текст, если корректен.
     * @throw cipher_error Если текст пуст или содержит строчные буквы.
     */
    std::wstring getValidCipherText(const std::wstring& s) const;

public:
    /// Без ключа нельзя.
    TableCipher() = delete;

    /**
     * @brief Конструктор шифра.
     * @param key Ключ (число столбцов).
     * @throw cipher_error Если ключ некорректен.
     */
    explicit TableCipher(int key);

    /**
     * @brief Шифрует текст.
     * @param open_text Открытый текст.
     * @return Шифротекст.
     * @throw cipher_error Если открытый текст некорректен.
     */
    std::wstring encrypt(const std::wstring& open_text) const;

    /**
     * @brief Расшифровывает текст.
     * @param cipher_text Шифротекст.
     * @return Открытый текст.
     * @throw cipher_error Если шифротекст некорректен.
     */
    std::wstring decrypt(const std::wstring& cipher_text) const;
};
