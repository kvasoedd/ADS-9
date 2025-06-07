// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <stdexcept>

class PMTree {
public:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        Node(char v) : value(v) {}
    };

    std::unique_ptr<Node> root;

    PMTree(const std::vector<char>& elements);

private:
    void build(std::unique_ptr<Node>& node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);

std::vector<char> getPerm1(const PMTree& tree, int num);

std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
