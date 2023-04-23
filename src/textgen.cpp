// Copyright 2021 GHA Test Team
#include "textgen.h"

#include <utility>

MarkovTextGenerator::MarkovTextGenerator(const std::wstring &text, int nPref) {
    if (nPref >= text.length())
        throw std::invalid_argument("Number of prefix must be < text length");

    table = std::map<prefix, suffix>();

    prefix pr = prefix();
    std::vector<std::wstring> words = split(text, L" ");
    for (int i = 0; i < nPref; i++) {
        pr.push_back(words[i]);
    }
    for (int i = nPref; i < words.size(); i++) {
        if (table.find(pr) == table.end()) {
            suffix sf = suffix();
            sf.push_back(words[i]);
            table[pr] = sf;
        } else {
            table[pr].push_back(words[i]);
        }
        pr.pop_front();
        pr.push_back(words[i]);
    }
}

MarkovTextGenerator::MarkovTextGenerator(std::map<prefix, suffix> table) {
    this->table = std::move(table);
}

std::wstring MarkovTextGenerator::GenerateText(int maxLen) {
    std::wstring text;
    prefix pr = table.begin()->first;
    std::srand(time(nullptr));
    while (text.length() < maxLen) {
        if (table.find(pr) == table.end()) {
            break;
        }
        suffix sf = table[pr];
        int id = std::rand() % sf.size();
        text += sf[id] + L" ";
        pr.pop_front();
        pr.push_back(sf[id]);
    }
    return text;
}

std::vector<std::wstring> split(const std::wstring &s,
                                const std::wstring &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::wstring token;
    std::vector<std::wstring> res;

    pos_end = s.find(delimiter, pos_start);
    while (pos_end != std::wstring::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
        pos_end = s.find(delimiter, pos_start);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

std::map<prefix, suffix> MarkovTextGenerator::GetTable() {
    return table;
}
