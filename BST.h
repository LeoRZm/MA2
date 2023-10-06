#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>

/*
*   TODOs
    Line 160: Implement Destructor
    Line 224: Implement printMaxPath
    Line 240: Implement contains
*/
using namespace std;

/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
    T value;
    Node* left;
    Node* right;

    Node(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {
protected:
    Node<T>* _root;         // Root of the tree nodes

    /* Add new T val to the tree */
    void addHelper(Node<T>* root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            }
            else {
                addHelper(root->left, val);
            }
        }
        else {
            if (!root->right) {
                root->right = new Node<T>(val);
            }
            else {
                addHelper(root->right, val);
            }
        }
    }

    /* Print tree out in inorder (A + B) */
    void printInOrderHelper(Node<T>* root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    /* Return number of nodes in tree */
    int nodesCountHelper(Node<T>* root) {
        if (!root) {
            return 0;
        }
        else {
            return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
        }
    }

    /* Return height of tree (root == nullptr -> 0) */
    int heightHelper(Node<T>* root) {
        if (!root) {
            return -1;
        }
        else {
            return 1 + max(heightHelper(root->left), heightHelper(root->right));
        }
    }

    /* Delete a given <T> value from tree */
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == nullptr || current->right == nullptr) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    }
                    else {
                        parent->right = temp;
                    }
                }
                else {
                    this->_root = temp;
                }
            }
            else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
            deleteValueHelper(current, current->right, value);
    }

    // Helper function to recursively destroy the tree
    void destroyTree(Node<T>* root) {
        if (root) {
            destroyTree(root->left);
            destroyTree(root->right);
            delete root;
        }
    }

    // Helper function to find and store the maximum path
    
    /********************************* PUBLIC API *****************************/
public:
    BST() : _root(nullptr) { }               // Basic initialization constructor
    /**
     * Destructor - Needs to free *all* nodes in the tree
     * TODO: Implement Destructor
     */
    /**
     * Destructor - Needs to free *all* nodes in the tree
     */
    ~BST() {
        destroyTree(_root);
    }

    /* Public API */
    void add(T val) {
        if (this->_root) {
            this->addHelper(this->_root, val);
        }
        else {
            this->_root = new Node<T>(val);
        }
    }

    void print() {
        printInOrderHelper(this->_root);
    }

    /**
     * Print the nodes level by level, starting from the root
     */
    void printLevelOrder() {
        if (!_root) return;

        queue<Node<T>*> q;
        q.push(_root);

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            cout << current->value << " ";

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        cout << endl;
    }

    int nodesCount() {
        return nodesCountHelper(this->_root);
    }

    int height() {
        return heightHelper(this->_root);
    }

    void findMaxPath(Node<T>* root, vector<T>& path) {
        if (!root) return;

        vector<T> leftPath;
        vector<T> rightPath;

        findMaxPath(root->left, leftPath);
        findMaxPath(root->right, rightPath);

        // Compare the sum of left and right paths
        if (accumulate(leftPath.begin(), leftPath.end(), 0) > accumulate(rightPath.begin(), rightPath.end(), 0)) {
            path = leftPath;
        }
        else {
            path = rightPath;
        }

        // Add the current node's value to the selected path
        path.insert(path.begin(), root->value);
    }

    /**
     * Print the maximum path in this tree
     */
    void printMaxPath() {
        if (!_root) return;

        vector<T> path;
        findMaxPath(_root, path);

        for (T value : path) {
            cout << value << " ";
        }
        cout << endl;
    }

    

    bool deleteValue(T value) {
        return this->deleteValueHelper(nullptr, this->_root, value);
    }

    /**
     * Find if the BST contains the value
     */
    bool contains(T value) {
        return containsHelper(_root, value);
    }

    // Helper function to recursively check if the tree contains a value
    bool containsHelper(Node<T>* root, T value) {
        if (!root) {
            return false;
        }

        if (root->value == value) {
            return true;
        }
        else if (root->value > value) {
            return containsHelper(root->left, value);
        }
        else {
            return containsHelper(root->right, value);
        }
    }
};

#endif
