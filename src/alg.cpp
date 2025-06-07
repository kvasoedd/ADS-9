// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <numeric>
#include <functional>

static long long factorial(int n) {
    static std::vector<long long> fact{1};
    while ((int)fact.size() <= n)
        fact.push_back(fact.back() * fact.size());
    return fact[n];
}

PMTree::PMTree(const std::vector<char>& elements) {
    root = std::make_unique<Node>('\0');
    build(root, elements);
}

void PMTree::build(std::unique_ptr<Node>& node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    std::sort(remaining.begin(), remaining.end());
    for (size_t i = 0; i < remaining.size(); ++i) {
        char val = remaining[i];
        auto child = std::make_unique<Node>(val);
        std::vector<char> next = remaining;
        next.erase(next.begin() + i);
        build(child, next);
        node->children.push_back(std::move(child));
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    std::function<void(const PMTree::Node*)> dfs = [&](const PMTree::Node* node) {
        if (node->value != '\0')
            path.push_back(node->value);
        if (node->children.empty()) {
            result.push_back(path);
        } else {
            for (auto& ch : node->children)
                dfs(ch.get());
        }
        if (node->value != '\0')
            path.pop_back();
    };
    dfs(tree.root.get());
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num < 1 || num > (int)all.size()) return {};
    return all[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    auto node = tree.root.get();
    std::vector<char> result;
    int n = node->children.size();
    long long total = factorial(n);
    if (num < 1 || num > total) return {};

    int k = num - 1;
    while (!node->children.empty()) {
        n = node->children.size();
        long long block = factorial(n - 1);
        int idx = k / block;
        result.push_back(node->children[idx]->value);
        node = node->children[idx].get();
        k %= block;
    }
    return result;
}
