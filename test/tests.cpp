// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(prefix_count, first) {
    std::wstring t = L"first second third";
    int nPref = 2;
    MarkovTextGenerator generator = MarkovTextGenerator(t, nPref);
    auto table = generator.GetTable();
    for (const auto& element : table) {
        EXPECT_EQ(element.first.size(), nPref);
    }
}

TEST(prefix_suffix_pair, pair) {
    std::wstring t = L"first second third";
    MarkovTextGenerator generator = MarkovTextGenerator(t);
    auto table = generator.GetTable();
    prefix pr = prefix();
    pr.emplace_back(L"first");
    pr.emplace_back(L"second");
    EXPECT_EQ(table[pr][0], L"third");
}

TEST(prefix_suffix_pair, one_suffix) {
    std::wstring t = L"first second";
    int nPref = 1;
    MarkovTextGenerator generator = MarkovTextGenerator(t, nPref);
    auto table = generator.GetTable();
    prefix pr = prefix();
    pr.emplace_back(L"first");
    EXPECT_EQ(table[pr][0], L"second");
}

TEST(prefix_suffix_pair, many_suffix) {
    std::wstring t = L"first first second";
    MarkovTextGenerator generator = MarkovTextGenerator(t, 1);
    auto table = generator.GetTable();
    prefix pr = prefix();
    pr.emplace_back(L"first");
    suffix sf = suffix();
    sf.emplace_back(L"first");
    sf.emplace_back(L"second");
    EXPECT_EQ(table[pr][0], sf[0]);
    EXPECT_EQ(table[pr][1], sf[1]);
}

TEST(text_generate, with_length) {
    auto table = std::map<prefix, suffix>();
    prefix pr = prefix();
    suffix sf = suffix();
    pr.emplace_back(L"first");
    sf.emplace_back(L"second");
    table[pr] = sf;
    pr.clear();
    pr.emplace_back(L"second");
    sf.clear();
    sf.emplace_back(L"first");
    table[pr] = sf;
    MarkovTextGenerator generator = MarkovTextGenerator(table);
    std::wstring expected = L"second first second first second first second ";
    expected += L"first second first second first second first second first ";
    EXPECT_EQ(expected, generator.GenerateText(100));
}