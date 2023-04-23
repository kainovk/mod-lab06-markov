// Copyright 2021 GHA Test Team
#pragma once

#include <cstdlib>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

typedef std::deque<std::wstring> prefix;
typedef std::vector<std::wstring> suffix;

class MarkovTextGenerator {
 public:
    explicit MarkovTextGenerator(const std::wstring& text, int nPref = 2);

    explicit MarkovTextGenerator(std::map<prefix, suffix> table);

    std::wstring GenerateText(int maxLen);

    std::map<prefix, suffix> GetTable();

 private:
    std::map<prefix, suffix> table;
};

std::vector<std::wstring> split(const std::wstring &s,
                                const std::wstring &delimiter);
