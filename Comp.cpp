#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "DOM.h"
#include "Tree.h"
#include "elements/Elements.h"

int main()
{

    std::ifstream input;
    input.open("index.cpj");
    std::vector<std::string> output = DOM::generateAST(&input);
    DOM::printVector(&output);
    std::cout << "\n";
    /*
    std::cout << DOM::checkForClosingTags(output) << "\n";
    NaryTree<char *> tree("root");
    tree.insert("root", "h1", "header");
    tree.insert("h1", "div", "elem");
    tree.insert("h1", "button", "butt");
    tree.insertWithId("header", "video", "vid");
    tree.print();
    std::cout << "\n";
    auto nodeOfH1 = tree.getElementById("butt");
    std::cout << nodeOfH1->data << std::endl;
    */
    // auto vec = DOM::getChildren(6, output);
    // DOM::printVector(&vec);
    //    int num = DOM::findeTag(std::string("<root>"), output);
    //  std::cout << DOM::hasChildren(12, output) << "\n";

    auto lexTree = DOM::produceLexTree(output);
    lexTree.print();
    auto tags = lexTree.getTags();
    DOM::printVector(&tags);
    if (DOM::compareVectors(output, tags))
    {
        std::cout << "Vectors are equal"
                  << "\n";
    }
    else
    {
        std::cout << "Vectors are not equal\n";
    }
    std::cout << getOne() << "\n";
    return 0;
}
