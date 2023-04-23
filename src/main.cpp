// Copyright 2021 GHA Test Team
#include <iostream>
#include "../include/textgen.h"

int main() {
    const int NPREF=2; // количество слов в префиксе
    const int MAXGEN=1000; //объем текста на выходе

    std::wstring text = L"In fields of gold, the flowers sway,\n"
                        "Dancing gently in the breeze all day,\n"
                        "Their petals soft, their colors bright,\n"
                        "A wonder to behold in the light.";
    MarkovTextGenerator generator = MarkovTextGenerator(text, NPREF);

    std::wcout << generator.GenerateText(MAXGEN);
}