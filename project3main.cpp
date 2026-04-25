#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

// Tree node structure
class Node {
public:
    string value;
    string label;
    int level;
    int position;
    Node *parent;
    vector<Node *> children;

    Node(string v, string lab = "", int lev = 0, int p = 1)
        : value(v), label(lab), level(lev), position(p), parent(nullptr) {}
};

// Build tree from file (assumes preorder-style structured input)
pair<Node *, vector<Node *>> tree(string filename)
{
    ifstream file(filename);
    string line;

    if (!file.is_open())
        return {nullptr, {}}; // file error

    Node *root = nullptr;
    vector<Node *> allNodes;

    while (getline(file, line))
    {
        stringstream stream(line);
        string value, label;
        int level, position;

        if (!(stream >> level >> position >> label))
            continue;

        getline(stream >> ws, value);

        Node *tempNode = new Node(value, label, level, position);

        // First node at level 0 becomes root
        if (level == 0)
            root = tempNode;

        // Find parent based on level (previous node with level-1)
        for (int i = allNodes.size() - 1; i >= 0; --i)
        {
            if (allNodes[i]->level == tempNode->level - 1)
            {
                tempNode->parent = allNodes[i];
                allNodes[i]->children.push_back(tempNode);
                break;
            }
        }

        allNodes.push_back(tempNode);
    }

    return {root, allNodes};
}

// Display node relationships (ancestor, descendant, sibling)
void display(int pos, const vector<Node *> &allNodes)
{
    Node *target = nullptr;

    for (auto node : allNodes)
        if (node->position == pos)
            target = node;

    if (!target)
    {
        cout << "Invalid input. Please try again." << endl;
        return;
    }

    cout << "\tDisplay" << endl;
    cout << "Content: " << target->value << endl;

    // Parent
    cout << "Ancestor: "
         << (target->parent ? target->parent->value : "None") << endl;

    // First child only (if exists)
    cout << "Descendant: "
         << (!target->children.empty() ? target->children[0]->value : "None") << endl;

    // Sibling search
    if (target->parent && target->parent->children.size() > 1)
    {
        for (auto sibling : target->parent->children)
        {
            if (sibling != target)
            {
                cout << "Sibling: " << sibling->value << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Sibling: None" << endl;
    }
}

// Preorder visualization
void visualization(Node *n)
{
    for (int i = 0; i < 2 * (n->level); i++)
        cout << "-";

    if (n->level > 0)
        cout << "[" << n->label << "]";

    cout << " " << n->value << endl;

    for (auto child : n->children)
        visualization(child);
}

// Height of tree (recursive)
int tree_height(Node *root)
{
    if (!root)
        return -1;

    int max_h = -1;

    for (auto node : root->children)
        max_h = max(max_h, tree_height(node));

    return max_h + 1;
}

// Collect internal nodes (preorder)
void preorder_internal(Node *root, ofstream &out)
{
    if (!root)
        return;

    if (!root->children.empty())
        out << root->value << ", ";

    for (auto node : root->children)
        preorder_internal(node, out);
}

// Collect external (leaf) nodes
void preorder_external(Node *root, ofstream &out)
{
    if (!root)
        return;

    if (root->children.empty())
        out << root->value << ", ";

    for (auto node : root->children)
        preorder_external(node, out);
}

// Compute tree statistics
void tree_properties(vector<Node *> allNodes, Node *root, ofstream &out)
{
    if (allNodes.empty())
        return;

    int internal = 0, external = 0;

    for (auto node : allNodes)
        (node->children.empty() ? external : internal)++;

    out << "1. Root node: " << root->value << endl;
    out << "2. Internal nodes: " << internal << endl;
    out << "3. Leaf nodes: " << external << endl;
    out << "4. Tree height: " << tree_height(root) << endl;

    out << "5. Internal (preorder): ";
    preorder_internal(root, out);
    out << endl;

    out << "6. External (preorder): ";
    preorder_external(root, out);
    out << endl;
}

// Binary tree check
bool isBinary(Node *root)
{
    if (!root)
        return true;

    if (root->children.size() > 2)
        return false;

    for (auto child : root->children)
        if (!isBinary(child))
            return false;

    return true;
}

// Proper binary tree check (0 or 2 children)
bool isProper(Node *root)
{
    if (!root)
        return true;

    if (!root->children.empty() && root->children.size() != 2)
        return false;

    for (auto child : root->children)
        if (!isProper(child))
            return false;

    return true;
}

// Count total nodes
int countNodes(Node *root)
{
    if (!root)
        return 0;

    int count = 1;

    for (auto child : root->children)
        count += countNodes(child);

    return count;
}

// Perfect tree check
bool isPerfect(Node *root)
{
    int h = tree_height(root);
    int total = countNodes(root);

    return total == (pow(2, h + 1) - 1);
}

// Balanced tree check
bool isBalanced(Node *root)
{
    if (!root)
        return true;

    vector<int> heights;

    for (auto child : root->children)
        heights.push_back(tree_height(child));

    for (int i = 0; i < heights.size(); i++)
        for (int j = i + 1; j < heights.size(); j++)
            if (abs(heights[i] - heights[j]) > 1)
                return false;

    for (auto child : root->children)
        if (!isBalanced(child))
            return false;

    return true;
}

// Write tree to file
void write_out(Node *n, ofstream &out)
{
    for (int i = 0; i < 2 * n->level; i++)
        out << "-";

    if (n->level > 0)
        out << "[" << n->label << "]";

    out << " " << n->value << endl;

    for (auto child : n->children)
        write_out(child, out);
}

// Main driver
int main()
{
    auto result = tree("tree-investment-1.txt");
    Node *root = result.first;
    vector<Node *> allNodes = result.second;

    bool running = true;
    string input;

    while (running)
    {
        cout << "Enter node position (or 'exit'): ";
        cin >> input;

        if (input == "exit")
        {
            cout << "Goodbye!" << endl;
            break;
        }

        try
        {
            int pos = stoi(input);
            display(pos + 1, allNodes);
        }
        catch (...)
        {
            cout << "Invalid input." << endl;
        }
    }

    ofstream out("about_tree.txt");

    out << "Tree Visualization\n";
    write_out(root, out);

    out << "\nTree Properties\n";
    tree_properties(allNodes, root, out);

    out << "\nBinary Tree Analysis\n";
    bool binary = isBinary(root);

    out << "Binary? " << (binary ? "Yes" : "No") << "\n";

    if (binary)
    {
        out << "Proper? " << (isProper(root) ? "Yes" : "No") << "\n";
        out << "Perfect? " << (isPerfect(root) ? "Yes" : "No") << "\n";
        out << "Balanced? " << (isBalanced(root) ? "Yes" : "No") << "\n";
    }

    out.close();
    return 0;
}