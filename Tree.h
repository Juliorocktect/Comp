#ifndef NARY_TREE_H
#define NARY_TREE_H

#include <vector>
#include <iostream>

template <typename T>
class NaryTreeNode
{
public:
    T data;
    std::vector<NaryTreeNode *> children;
    std::string id;

    NaryTreeNode(const T &val) : data(val) { id = nullptr; }
    NaryTreeNode(const T &val, const char *pId)
    {
        data = val;
        id = std::string(pId);
    }
};

template <typename T>
class NaryTree
{
private:
    NaryTreeNode<T> *root;

    std::vector<T> inOrder(NaryTreeNode<T> *node, std::vector<T> *elements)
    {
        if (node != nullptr)
        {
            elements->push_back(node->data);
            for (NaryTreeNode<T> *n : node->children)
            {
                inOrder(n, elements);
            }
        }
        return *elements;
    }
    NaryTreeNode<T> *getNodeById(NaryTreeNode<T> *node, std::string id)
    {
        if (node)
        {
            if (!node->id.compare(std::string(id)))
                return node;
            else
            {
                for (auto child : node->children)
                {
                    getNodeById(child, id);
                }
            }
        }
    }
    void insertById(NaryTreeNode<T> *node, const T &val, const char *parentId, const char *childId)
    {
        if (node)
        {
            if (node->id.compare(std::string(parentId)))
            {
                node->children.push_back(new NaryTreeNode<T>(val, childId));
                return;
            }
            for (auto n : node->children)
            {
                insertById(n, val, parentId, childId);
            }
        }
    }
    void destroyTree(NaryTreeNode<T> *node)
    {
        if (node)
        {
            for (auto child : node->children)
            {
                destroyTree(child);
            }
            delete node;
        }
    }

public:
    NaryTree() : root(nullptr) {}
    NaryTree(const T content)
    {
        root = new NaryTreeNode<T>(content, "root");
    }
    ~NaryTree()
    {
        destroyTree(root);
    }
    NaryTreeNode<T> *getElementById(const char *id)
    {
        return getNodeById(root, id);
    }
    std::vector<T> getTags()
    {
        std::vector<T> elements;
        return inOrder(root, &elements);
    }

    void insert(const T &parentVal, const T &val, const char *id)
    {
        if (root == nullptr)
        {
            root = new NaryTreeNode<T>(val, id);
            return;
        }
        insert(root, parentVal, val, id);
    }

    void insertWithId(const char *partentId, const T &val, const char *childId)
    {
        insertById(root, val, partentId, childId);
    }

    void insert(NaryTreeNode<T> *node, const T &parentVal, const T &val, const char *id)
    {
        if (!node)
            return;

        if (node->data == parentVal)
        {
            node->children.push_back(new NaryTreeNode<T>(val, id));
            return;
        }

        for (auto child : node->children)
        {
            insert(child, parentVal, val, id);
        }
    }

    void print()
    {
        print(root, 0);
    }

    void print(NaryTreeNode<T> *node, int depth)
    {
        if (!node)
            return;

        for (int i = 0; i < depth; ++i)
            std::cout << "-";

        std::cout << node->data << std::endl;

        for (auto child : node->children)
        {
            print(child, depth + 1);
        }
    }
};

#endif // NARY_TREE_H