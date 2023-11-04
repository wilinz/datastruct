#include <iostream>
#include <queue>
#include <functional>

using namespace std;

// 二叉树节点的定义
template<typename T>
struct TreeNode {
    // 节点的值
    T val;
    // 左子节点
    TreeNode<T> *left;
    // 右子节点
    TreeNode<T> *right;
    // 父节点
    TreeNode<T> *parent;

    TreeNode(T x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

// 按层次顺序构建二叉树
template<typename T>
TreeNode<T> *buildTree() {
    queue<pair<TreeNode<T>*, int>> q;  // 使用pair记录节点和层级信息
    cout << "输入根节点的值（空节点输入为空）：";
    string input;
    cin >> input;
    TreeNode<T> *root = nullptr;

    if (input != "NULL") {
        T val = stoi(input);
        root = new TreeNode<T>(val);
        q.push({root, 0});  // 根节点的层级为0
    }

    while (!q.empty()) {
        TreeNode<T> *node = q.front().first;
        int level = q.front().second;
        q.pop();

        cout << "输入第 " << level + 1 << " 层节点 " << node->val << " 的左子节点的值（空节点输入为空）：";
        cin >> input;
        if (input != "n") {
            T val = stoi(input);
            node->left = new TreeNode<T>(val);
            node->left->parent = node;  // 设置左子节点的父节点
            q.push({node->left, level + 1});  // 左子节点的层级为当前节点层级加1
        }

        cout << "输入第 " << level + 1 << " 层节点 " << node->val << " 的右子节点的值（空节点输入为空）：";
        cin >> input;
        if (input != "n") {
            T val = stoi(input);
            node->right = new TreeNode<T>(val);
            node->right->parent = node; // 设置右子节点的父节点
            q.push({node->right, level + 1}); // 右子节点的层级为当前节点层级加1
        }
    }

    return root;
}


// 先序遍历二叉树
template<typename T>
void preorderTraversal(TreeNode<T> *root) {
    if (root == nullptr) {
        return;
    }

    // 访问根节点
    cout << root->val << " ";
    // 递归遍历左子树
    preorderTraversal(root->left);
    // 递归遍历右子树
    preorderTraversal(root->right);
}

// 中序遍历二叉树
template<typename T>
void inorderTraversal(TreeNode<T> *root) {
    if (root == nullptr) {
        return;
    }

    // 递归遍历左子树
    inorderTraversal(root->left);
    // 访问根节点
    cout << root->val << " ";
    // 递归遍历右子树
    inorderTraversal(root->right);
}

// 后序遍历二叉树
template<typename T>
void postorderTraversal(TreeNode<T> *root) {
    if (root == nullptr) {
        return;
    }

    // 递归遍历左子树
    postorderTraversal(root->left);
    // 递归遍历右子树
    postorderTraversal(root->right);
    // 访问根节点
    cout << root->val << " ";
}

// 按层次遍历二叉树
template<typename T>
void levelOrderTraversal(TreeNode<T> *root) {
    if (root == nullptr) {
        return;
    }

    queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<T> *node = q.front();
        q.pop();
        cout << node->val << " ";

        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}

template<typename T>
void printTreeShape(TreeNode<T> *root) {
    if (root == nullptr) {
        return;
    }

    queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();  // 获取当前层的节点数量

        for (int i = 0; i < size; i++) {
            TreeNode<T> *node = q.front();
            q.pop();
            if (node == nullptr) {
                continue;
            }
            if (node->parent) {
                cout << "(" << node->parent->val << ")";
            }

            cout << node->val << " ";

            q.push(node->left);
            q.push(node->right);
        }

        cout << endl;  // 在每一层结束后添加换行符
    }
}


int main() {
    cout << "按层次顺序建立二叉树：" << endl;
    TreeNode<int> *root = buildTree<int>();

    cout << "形状：" << endl;
    printTreeShape(root);
    cout << endl;

    cout << "先序遍历二叉树：";
    preorderTraversal(root);
    cout << endl;

    cout << "中序遍历二叉树：";
    inorderTraversal(root);
    cout << endl;

    cout << "后序遍历二叉树：";
    postorderTraversal(root);
    cout << endl;

    cout << "按层次遍历二叉树：";
    levelOrderTraversal(root);
    cout << endl;

    return 0;
}
