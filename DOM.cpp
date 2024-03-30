#include "DOM.h"

// TODO: rename method
std::vector<std::string> DOM::generateAST(std::ifstream *input)
{
    std::string line;
    if (input->is_open()) // check for open file
    {
        std::vector<std::string> marked;
        std::string markedWord;
        std::vector<bool> closed;
        while (getline(*input, line))
        {
            bool mark = false;
            for (int i = 0; i < line.length(); i++) // tokenize elements
            {
                if (line[i] == '<')
                {
                    mark = true;
                }
                if (mark && line[i] != '>')
                {
                    markedWord += line[i];
                }
                if (line[i] == '>' && mark)
                {
                    marked.push_back(markedWord + line.at(i));
                    markedWord = "";
                    mark = false;
                }
            }
        }
        input->close();
        return marked;
    }
}
std::string DOM::getClosing(std::string tag)
{
    std::string closingTag = tag.substr(1, tag.size());
    tag = "</" + closingTag;
    return tag;
}
bool DOM::checkForClosingTags(std::vector<std::string> &tokens)
{
    std::stack<std::string> stack;
    for (int i = 0; i < tokens.size(); i++)
    {
        std::string nameOfTag = tokens[i].substr(1, tokens[i].find('>' - 1));
        if (nameOfTag.front() == '/')
        {
            nameOfTag = nameOfTag.substr(1);
            if (stack.empty() || stack.top() != nameOfTag)
                return false;
            stack.pop();
        }
        else
        {
            stack.push(nameOfTag);
        }
    }
    return stack.empty();
}
NaryTree<std::string> DOM::produceLexTree(std::vector<std::string> &tokens)
{
    NaryTree<std::string> tree;
    tree.insert("", "<root>", "");
    for (int i = 0; i < tokens.size(); i++) // für jedes element die kinde bekommen
    {
        if (hasChildren(i, tokens))
        {
            auto children = getChildren(i, tokens);
            for (int j = 0; j < children.size(); j++)
            {
                tree.insert(tokens[i], children[j], "");
            }
        }
    }
    return tree;
}
int DOM::findeTag(std::string tag, std::vector<std::string> &tokens)
{
    std::string close = getClosing(tag);
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].compare(close) == 0)
        {
            return i;
        }
    }
    return -1;
}
bool DOM::isClosing(std::string tag)
{
    return tag.find('/') != std::string::npos;
}
std::vector<std::string> DOM::getChildren(int position, std::vector<std::string> &tokens)
{
    std::string closingTag = tokens[position].substr(1, tokens[position].size());
    std::string close = "</" + closingTag;
    closingTag.~basic_string();
    std::vector<std::string> result;
    position++;
    for (int i = position; i < tokens.size() && tokens[i].compare(close); i++)
    {
        if (tokens[i].compare(close))
        {
            if (hasChildren(i, tokens))
            {
                // std::cout << i << " has children\n";
                int ende = findeTag(tokens[i], tokens);
                result.push_back(tokens[i]);
                i = ende - 1;
            }
            else
            {
                result.push_back(tokens[i]);
                // std::cout << i << "\n";
            }
        }
    }
    if (position == 1)
    {
        result.push_back("</root>");
    }
    return result;
}
// check was der parent(name) in variable
// gehe durch array, bis parent(/name) gefunden -> für jeden durchlauf zählvariable hochzählen und wird zurückgegeben

// nimm zählvariable uun nimm die position zieh ab und aufaddiren
bool DOM::hasChildren(int position, std::vector<std::string> &tokens)
{
    if (isClosing(tokens[position]))
        return false;
    std::string closingTag = tokens[position].substr(1, tokens[position].size());
    std::string close = "</" + closingTag;
    return tokens[position + 1].compare(close);
}

bool DOM::compareVectors(std::vector<std::string> &vecA, std::vector<std::string> &vecB)
{
    if (vecA.size() != vecB.size())
        return 0;
    for (int i = 0; i < vecA.size(); i++)
    {
        if (vecA[i].compare(vecB[i]) != 0)
        {
            return 0;
        }
    }
    return 1;
}