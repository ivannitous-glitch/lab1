#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>


std::locale loc("ru_RU.UTF-8");

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(skey);
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(open_text);
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(cipher_text);
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (wchar_t c : s) {
        // Проверяем, что символ есть в алфавите
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        } else {
            // Если символа нет в алфавите, используем 0 (можно изменить на обработку ошибки)
            result.push_back(0);
        }
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (int i : v) {
        if (i >= 0 && i < (int)numAlpha.size()) {
            result += numAlpha[i];
        } else {
            result += L'?'; // Заменяем невалидные индексы на '?'
        }
    }
    return result;
}