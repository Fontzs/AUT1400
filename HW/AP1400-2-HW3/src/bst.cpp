#include "bst.h"

// #include <format>

BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node& node) { Node(node.value, node.left, node.right); }

BST::BST() { this->root == nullptr; }

BST::Node* copyTree(BST::Node* root) {
    if (root == nullptr)
        return nullptr;
    BST::Node* newRoot = new BST::Node(root->value, nullptr, nullptr);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

BST::BST(const BST& b) {
    if (b.root == nullptr)
        this->root = nullptr;
    this->root = copyTree(b.root);
}

BST::BST(BST&& b) {
    this->root = b.root;
    b.root = nullptr;
}

BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes) delete node;
}

BST::Node*& BST::get_root() { return this->root; }

// BSF search
void BST::bfs(std::function<void(Node*& node)> func) {
    auto lam = [&func](Node* root) -> bool {
        if (root == nullptr)
            return false;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            Node* left = temp->left;
            Node* right = temp->right;
            if (left != nullptr)
                q.push(left);
            if (right != nullptr)
                q.push(right);
            func(temp);
        }
        return true;
    };

    lam(this->root);
}

// DFS search ?

int num(BST::Node* node) {
    if (node == nullptr)
        return 0;
    else {
        return 1 + num(node->left) + num(node->right);
    }
}

size_t BST::length() { return num(this->root); }

bool BST::add_node(int value) {
    Node* p = this->root;
    if (p == nullptr) {
        p = new Node(value, nullptr, nullptr);
        return true;
    }
    while (p->left != nullptr || p->right != nullptr) {
        if (value < p->value) {
            if (p->left == nullptr)
                break;
            p = p->left;
        } else if (value > p->value) {
            if (p->right == nullptr)
                break;
            p = p->right;
        } else {
            break;
        }
    }
    if (p->value == value) {
        return false;
    }
    if (p->value < value) {
        p->right = new Node(value, nullptr, nullptr);
    } else {
        p->left = new Node(value, nullptr, nullptr);
    }
    return true;
}

BST::Node** BST::find_node(int value) {
    if (this->root->value == value) {
        return &(this->root);
    }
    Node* p = this->root;
    while (p != nullptr) {
        if (p->value < value) {
            p = p->right;
        } else if (p->value > value) {
            p = p->left;
        } else {
            break;
        }
    }
    if (p == nullptr) {
        return nullptr;
    }
    return &p;
}

BST::Node** BST::find_parrent(int value) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return nullptr;
    }
    if (find_node(value) == nullptr)
        return nullptr;
    Node* p = this->root;
    while (p->left->value != value && p->right->value != value) {
        if (p->value < value) {
            p = p->right;
        } else {
            p = p->left;
        }
    }
    return &p;
}

BST::Node** BST::find_successor(int value) {
    Node** p = find_node(value);
    if (p == nullptr)
        return nullptr;
    return (*p)->left == nullptr ? &((*p)->right) : &((*p)->left);
}

bool BST::delete_node(int value) {
    if (find_node(value) == nullptr)
        return false;
    Node* parent = *(find_parrent(value));
    Node* node = *(find_node(value));
    if (node->left == nullptr && node->right == nullptr) {
        if (value > parent->value) {
            parent->right = nullptr;
            return true;
        } else {
            parent->left = nullptr;
            return true;
        }
    } else if (node->left != nullptr && node->right == nullptr) {
        if (value > parent->value) {
            parent->right = node->left;
            free(node);
            return true;
        } else {
            parent->left = node->left;
            free(node);
            return true;
        }
    } else if (node->right != nullptr && node->left == nullptr) {
        if (value > parent->value) {
            parent->right = node->right;
            free(node);
            return true;
        } else {
            parent->left = node->right;
            free(node);
            return true;
        }
    } else {
        if (value > parent->value) {
            node->left->right = node->right;
            parent->right = node->left;
            free(node);
            return true;
        } else {
            node->left->right = node->right;
            parent->left = node->left;
            free(node);
            return true;
        }
    }
}

ostream& operator<<(ostream& os, BST::Node node) {
    os << "node: " << &node << "\nleft: " << node.left << "\nright" << node.right << "\n";
    return os;
}

bool operator==(const BST::Node& node, const int& num) { return node.value == num; }
bool operator==(const int& num, const BST::Node& node) { return num == node.value; }

bool operator<(const int& num, const BST::Node& node) { return num < node.value; }
bool operator<(const BST::Node& node, const int& num) { return node.value < num; }

bool operator<=(const int& num, const BST::Node& node) { return num <= node.value; }
bool operator<=(const BST::Node& node, const int& num) { return node.value <= num; }

bool operator>(const int& num, const BST::Node& node) { return num > node.value; }
bool operator>(const BST::Node& node, const int& num) { return node.value > num; }

bool operator>=(const int& num, const BST::Node& node) { return num >= node.value; }
bool operator>=(const BST::Node& node, const int& num) { return node.value >= num; }

ostream& operator<<(ostream& os, BST b) {
    os << "********************************************************************************\n";
    if (b.root == nullptr) {
    } else {
        queue<BST::Node*> q;
        q.push(b.root);
        while (!q.empty()) {
            BST::Node* temp = q.front();
            q.pop();
            BST::Node* left = temp->left;
            BST::Node* right = temp->right;
            if (left != nullptr)
                q.push(left);
            if (right != nullptr)
                q.push(right);
            os << std::format("%-17p=> value:%-10d", 7, temp->value);
            if (temp->left == nullptr) {
                os << "left:0               ";
            } else {
                os << std::format("left:%-16p", temp->left);
            }
            if (temp->right == nullptr) {
                os << "right:0               ";
            } else {
                os << std::format("right:%-16p", temp->right);
            }
            os << "\n";
        }
    }
    os << "binary search tree size: " << b.length() << "\n";
    os << "********************************************************************************\n";
    return os;
}

//++bst
BST& BST::operator++() {
    auto plus = [](BST::Node*& node) { node->value += 1; };
    bfs(plus);
    return *this;
}

BST BST::operator++(int) {
    BST b = BST(*this);
    auto plus = [](BST::Node*& node) { node->value += 1; };
    bfs(plus);
    return b;
}