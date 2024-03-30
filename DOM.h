#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include "Tree.h"

namespace DOM
{
    std::vector<std::string> generateAST(std::ifstream *input);
    bool checkForClosingTags(std::vector<std::string> &tokens);
    NaryTree<std::string> produceLexTree(std::vector<std::string> &tokens);
    int findeTag(std::string tag, std::vector<std::string> &tokens);
    bool isClosing(std::string tag);
    std::vector<std::string> getChildren(int position, std::vector<std::string> &tokens);
    bool hasChildren(int position, std::vector<std::string> &tokens);
    std::string getClosing(std::string tag);
    bool compareVectors(std::vector<std::string> &vecA, std::vector<std::string> &vecB);
    template <typename T>
    void printVector(std::vector<T> *vec)
    {
        for (int i = 0; i < vec->size(); i++)
        {
            std::cout << i << "     " << vec[0][i] << std::endl;
        }
    }
};