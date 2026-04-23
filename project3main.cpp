// Imports
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

// Create Node Class
class Node
{
public:
    string value; // What is in the node
    string label; // (Yes/No/NULL)
    int level;
    int position;
    Node *parent;
    vector<Node *> children; // Vector of the node's children

    Node(string v, string lab = "", int lev = 0, int p = 1) : value(v), label(lab), level(lev), position(p), parent(nullptr) {}
};

// Create binary tree from txt file
pair<Node *, vector<Node *>> tree(string filename)
{
    ifstream file(filename);
    string line;

    if (!file.is_open())
        return {nullptr, {}}; // Return if file didn't open

    Node *root = nullptr;
    vector<Node *> allNodes;

    // Handles rest of text
    while (getline(file, line))
    {
        stringstream stream(line);
        string value, label;
        int level, position;

        // Assigns parts of the text to variables
        if (!(stream >> level >> position >> label))
            continue;

        getline(stream >> ws, value);

        Node *tempNode = new Node(value, label, level, position);

        // Root case
        if (level == 0)
        {
            root = tempNode;
        }

        // Traverse allNodes to connect newNode with its parent
        for (int i = allNodes.size() - 1; i >= 0; --i)
        {
            if (allNodes[i]->level == tempNode->level - 1)
            { // Preorder forces parent's level to be 1 less
                tempNode->parent = allNodes[i];
                allNodes[i]->children.push_back(tempNode);
                break;
            }
        }
        allNodes.push_back(tempNode);
    }
    return {root, allNodes};
};

// Displays content, and one (ancestor, descendant, and sibling)
void display(int pos, const vector<Node *> &allNodes)
{
    Node *target = nullptr;

    for (auto node : allNodes)
    {
        if (node->position == pos)
        {
            target = node;
            break;
        }
    }

    if (!target)
    {
        cout << "Invalid input. Please try again." << endl;
        return;
    }
    cout << "\tDisplay" << endl;
    cout << "Content: " << target->value << endl;

    // Ancestor
    if (target->parent)
        cout << "Ancestor: " << target->parent->value << endl;
    else
        cout << "Ancestor: None" << endl;

    // Descendant
    if (!target->children.empty())
        cout << "Descendant: " << target->children[0]->value << endl;
    else
        cout << "Descendant: None" << endl;

    // Sibling
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

void visualization(Node *n)
{
    for (int i = 0; i < 2 * (n->level); i++)
        cout << "-";
    if (n->level > 0)
        cout << "[" << n->label << "]";
    cout << " " << n->value << endl;
    for (auto child : n->children)
    {
        visualization(child);
    }
};

int tree_height(Node *root)
{
    int max_tree_height = -1;

    if (!root)
        return -1;
    for (auto node : root->children)
    {
        max_tree_height = max(max_tree_height, tree_height(node));
    }
    return max_tree_height + 1;
};

// Finds internal nodes
void preorder_internal(Node *root, ofstream &out)
{
    if (!root)
        return;

    if (!root->children.empty())
        out << root->value << ", ";

    for (auto node : root->children)
        preorder_internal(node, out);
}

// Finds external nodes
void preorder_external(Node *root, ofstream &out)
{
    if (!root)
        return;

    if (root->children.empty())
        out << root->value << ", ";

    for (auto node : root->children)
        preorder_external(node, out);
}

void tree_properties(vector<Node *> allNodes, Node *root, ofstream &out)
{
    int internal_counter = 0;
    int external_counter = 0;
    for (auto internal_nodes : allNodes)
    {
        if (internal_nodes->children.empty())
            external_counter++;
        else
            internal_counter++;
    }
    if (allNodes.empty())
        return;

    out << "1. Root node: " << root->value << endl;
    out << "2. Number of internal nodes: " << internal_counter << endl;
    out << "3. Number of external (leaf) nodes: " << external_counter << endl;
    out << "4. Tree height: " << tree_height(root) << endl;
    out << "5. Internal nodes(preorder): ";
    preorder_internal(root, out);
    out << endl;
    out << "6. External nodes(preorder): ";
    preorder_external(root, out);
    out << endl;
};

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

int countNodes(Node *root)
{
    if (!root)
        return 0;

    int count = 1;
    for (auto child : root->children)
        count += countNodes(child);

    return count;
}

bool isPerfect(Node *root)
{
    int h = tree_height(root);
    int total = countNodes(root);

    return total == (pow(2, h + 1) - 1);
}

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

int main()
{
    // Creates tree from text file
    auto result = tree("tree-investment-1.txt");
    Node *root = result.first;
    vector<Node *> allNodes = result.second;

    bool running = true;
    string input;

    // Allows program to run until stated otherwise
    while (running)
    {
        cout << "Which node would you like to explore (enter position or \"exit\"): " << endl;
        cin >> input;

        // Exit check
        if (input == "exit")
        {
            cout << "Goodbye!" << endl;
            running = false;
            break;
        }
        else
        {
            // Displays position information
            try
            {
                int position = stoi(input);
                display(position + 1, allNodes);
            }
            catch (invalid_argument &e)
            {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
        }
    }

    ofstream out("about_tree.txt");

    out << "Tree Visualization\n";
    write_out(root, out);
    out << "\n";
    tree_properties(allNodes, root, out);

    out << "\nBinary Tree Analysis\n";

    bool binary = isBinary(root);
    out << "Is Binary Tree? " << (binary ? "Yes" : "No") << "\n";

    if (binary)
    {
        out << "Proper Tree? " << (isProper(root) ? "Yes" : "No") << "\n";
        out << "Perfect Tree? " << (isPerfect(root) ? "Yes" : "No") << "\n";
        out << "Balanced Tree? " << (isBalanced(root) ? "Yes" : "No") << "\n";
    }

    out.close();

    return 0;
}