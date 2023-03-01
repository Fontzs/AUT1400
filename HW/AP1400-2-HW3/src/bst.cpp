#include "bst.h"
BST::Node* copyTree(BST::Node* root);
// #include <format>

// Node's constructors
BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node& node) {
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}

// overload Node's << operator
ostream& operator<<(ostream& os, BST::Node node) {
    os << "node: " << &node << "\nvalue: " << node.value << "\nleft: " << node.left << "\nright"
       << node.right << "\n";
    return os;
}

// overload Node's ==, <, <=, >, >= operators
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

BST::BST() { this->root = nullptr; }

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

BST::BST(std::initializer_list<int> list) {
    this->root = nullptr;
    if (list.size() == 0) {
    } else {
        for (auto num : list) {
            add_node(num);
        }
    }
}

BST& BST::operator=(BST& b) {
    this->root = copyTree(b.root);
    return *this;
}

BST& BST::operator=(BST&& b) {
    this->root = b.root;
    b.root = nullptr;
    return *this;
}

// BST's functions
BST::Node* BST::get_root() { return this->root; }
// BSF search: use queue
void BST::bfs(std::function<void(Node*& node)> func) {
    if (this->root == nullptr)
        return;
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

size_t BST::length() const { return num(this->root); }

bool BST::add_node(int value) {
    if (this->root == nullptr) {
        this->root = new Node(value, nullptr, nullptr);
        return true;
    }
    Node* p = this->root;
    while (true) {
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
    if (p->value < value) {
        p->right = new Node(value, nullptr, nullptr);
        return true;
    } else if (p->value > value) {
        p->left = new Node(value, nullptr, nullptr);
        return true;
    } else {
        return false;
    }
}

// 傻逼玩样，二级指针，rnm

BST::Node** BST::find_node(int value) {
    auto cur = get_root();
    while (cur != nullptr) {
        if (value > cur->value) {
            cur = cur->right;
        } else if (value < cur->value) {
            cur = cur->left;
        } else {
            break;
        }
    }
    if (cur == nullptr)
        return nullptr;
    else {
        auto res = new Node* {cur};
        return res;
    }
}

BST::Node** BST::find_parrent(int value) {
    Node* current = get_root();
    Node* pre = nullptr;
    while (current != nullptr) {
        if (value > current->value) {
            pre = current;
            current = current->right;
        } else if (value < current->value) {
            pre = current;
            current = current->left;
        } else {
            break;
        }
    }
    if (current == nullptr)
        return nullptr;
    else {
        auto res{new Node* {pre}};
        return res;
    }
}

BST::Node** BST::find_successor(int value) {
    if (root == nullptr)
        return nullptr;
    auto b = find_node(value);
    if (b == nullptr || (*b)->left == nullptr) {
        delete b;
        return nullptr;
    }
    auto p = (*b)->left;
    while (p->right != nullptr) {
        p = p->right;
    }
    auto res{new Node* {p}};
    delete b;
    return res;
}

int MostLeftOnRight(BST::Node* n) {
    BST::Node* p = n;
    while (p->left != nullptr) p = p->left;
    return p->value;
}

bool BST::delete_node(int value) {
    auto node = find_node(value);
    auto parent = find_parrent(value);

    // 404 not found
    if (node == nullptr) {
        return false;
    }

    if ((*node)->left == nullptr && (*node)->right == nullptr) {
        if (get_root() == *node)
            root = nullptr;
        else {
            if (value > (*parent)->value)
                (*parent)->right = nullptr;
            else
                (*parent)->left = nullptr;
        }

    } else if ((*node)->left != nullptr && (*node)->right != nullptr) {
        auto next = find_successor(value);
        auto new_one = new Node{(*next)->value, (*node)->left, (*node)->right};
        delete_node((*next)->value);
        delete next;
        if (get_root() == *node) {
            new_one->left = root->left;
            new_one->right = root->right;
            root = new_one;
        } else {
            if ((*parent)->left == *node)
                (*parent)->left = new_one;
            else
                (*parent)->right = new_one;
        }
    } else {
        Node* new_one = nullptr;
        if ((*node)->left)
            new_one = (*node)->left;
        else
            new_one = (*node)->right;

        if (root == *node) {
            new_one->left = root->left;
            new_one->right = root->right;
            root = new_one;
        } else {
            if ((*parent)->left == *node)
                (*parent)->left = new_one;
            else
                (*parent)->right = new_one;
        }
    }
    delete *node;
    delete node;
    delete parent;

    return true;
}

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
            char buffer1[120];
            sprintf(buffer1, "%-17p=> value:%-10d", temp, temp->value);
            os << buffer1;
            if (temp->left == nullptr) {
                os << "left:0               ";
            } else {
                char buffer2[120];
                sprintf(buffer2, "left:%-16p", temp->left);
                os << buffer2;
            }
            if (temp->right == nullptr) {
                os << "right:0               ";
            } else {
                char buffer3[120];
                sprintf(buffer3, "right:%-16p", temp->right);
                os << buffer3;
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