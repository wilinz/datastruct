#include <iostream>

// 定义一个模板结构体，表示链表节点
template<typename T>
struct ListNode {
    T val; // 节点值
    ListNode *next; // 指向下一个节点的指针
    ListNode(T x) : val(x), next(nullptr) {} // 构造函数，初始化节点值和指针
};

// 定义一个模板类，表示链表
template<typename T>
class LinkedList {
public:
    ListNode<T> *head; // 指向链表头节点的指针

    // 构造函数，初始化链表
    LinkedList() : head(nullptr) {}

    // 插入节点的函数
    void insert(T val, bool reverse = false);

    // 打印链表的函数
    void print();

    // 求两个链表的交集的函数
    LinkedList<T> intersection(LinkedList<T> &other);

    // 求两个链表的并集的函数
    LinkedList<T> unionList(LinkedList<T> &other);

    // 判断链表中是否包含某个值的函数
    bool contains(T val);

    // 反转链表的函数
    void reverse();

    // 合并两个有序链表的函数
    LinkedList<T> merge(LinkedList<T> &other);

    // 复制链表的函数
    LinkedList<T> duplicate();
};

// 复制链表的函数
template<typename T>
LinkedList<T> LinkedList<T>::duplicate() {
    LinkedList<T> result; // 创建一个新的链表对象
    ListNode<T> *node = head; // 遍历原链表的指针
    while (node) {
        result.insert(node->val); // 将原链表节点的值插入到新链表中两次
        result.insert(node->val);
        node = node->next; // 移动到下一个节点
    }
    return result; // 返回复制后的链表
}

// 合并两个有序链表的函数
template<typename T>
LinkedList<T> LinkedList<T>::merge(LinkedList<T> &other) {
    LinkedList<T> result; // 创建一个新的链表对象
    ListNode<T> *nodeA = head; // 遍历第一个链表的指针
    ListNode<T> *nodeB = other.head; // 遍历第二个链表的指针
    while (nodeA && nodeB) {
        if (nodeA->val > nodeB->val) { // 如果第一个链表节点的值大于第二个链表节点的值
            result.insert(nodeA->val); // 将第一个链表节点的值插入到新链表中
            nodeA = nodeA->next; // 移动到下一个节点
        } else {
            result.insert(nodeB->val); // 将第二个链表节点的值插入到新链表中
            nodeB = nodeB->next; // 移动到下一个节点
        }
    }
    while (nodeA) {
        result.insert(nodeA->val); // 将第一个链表剩余节点的值插入到新链表中
        nodeA = nodeA->next; // 移动到下一个节点
    }
    while (nodeB) {
        result.insert(nodeB->val); // 将第二个链表剩余节点的值插入到新链表中
        nodeB = nodeB->next; // 移动到下一个节点
    }
    return result; // 返回合并后的链表
}

// 反转链表的函数
template<typename T>
void LinkedList<T>::reverse() {
    ListNode<T> *prev = nullptr; // 前一个节点的指针
    ListNode<T> *current = head; // 当前节点的指针
    ListNode<T> *next = nullptr; // 下一个节点的指针
    while (current != nullptr) {
        next = current->next; // 保存下一个节点的指针
        current->next = prev; // 将当前节点的指针指向前一个节点
        prev = current; // 更新前一个节点的指针
        current = next; // 更新当前节点的指针
    }
    head = prev; // 更新链表头节点的指针
}

// 判断链表中是否包含某个值的函数
template<typename T>
bool LinkedList<T>::contains(T val) {
    ListNode<T> *node = head; // 遍历链表的指针
    while (node) {
        if (node->val == val) { // 如果节点的值等于目标值
            return true; // 返回true
        }
        node = node->next; // 移动到下一个节点
    }
    return false; // 链表中不包含目标值，返回false
}

// 求两个链表的并集的函数
template<typename T>
LinkedList<T> LinkedList<T>::unionList(LinkedList<T> &other) {
    LinkedList<T> result; // 创建一个新的链表对象
    ListNode<T> *node = head; // 遍历第一个链表的指针
    while (node) {
        result.insert(node->val); // 将第一个链表节点的值插入到新链表中
        node = node->next; // 移动到下一个节点
    }
    node = other.head; // 遍历第二个链表的指针
    while (node) {
        if (!result.contains(node->val)) { // 如果新链表中不包含第二个链表节点的值
            result.insert(node->val); // 将第二个链表节点的值插入到新链表中
        }
        node = node->next; // 移动到下一个节点
    }
    return result; // 返回并集链表
}

// 求两个链表的交集的函数
template<typename T>
LinkedList<T> LinkedList<T>::intersection(LinkedList<T> &other) {
    LinkedList<T> result; // 创建一个新的链表对象
    ListNode<T> *nodeA = head; // 遍历第一个链表的指针
    while (nodeA) {
        ListNode<T> *nodeB = other.head; // 遍历第二个链表的指针
        bool found = false; // 是否找到交集节点的标志
        while (nodeB) {
            if (nodeA->val == nodeB->val) { // 如果第一个链表节点的值等于第二个链表节点的值
                found = true; // 设置找到交集节点的标志为true
                break; // 跳出内层循环
            }
            nodeB = nodeB->next; // 移动到第二个链表的下一个节点
        }
        if (found) {
            result.insert(nodeA->val); // 将交集节点的值插入到新链表中
        }
        nodeA = nodeA->next; // 移动到第一个链表的下一个节点
    }
    return result; // 返回交集链表
}

// 打印链表的函数
template<typename T>
void LinkedList<T>::print() {
    ListNode<T> *node = head; // 遍历链表的指针
    while (node) {
        std::cout << node->val << " "; // 输出节点的值
        node = node->next; // 移动到下一个节点
    }
    std::cout << std::endl; // 输出换行符
}

// 插入节点的函数
template<typename T>
void LinkedList<T>::insert(T val, bool reverse) {
    ListNode<T> *node = new ListNode<T>(val); // 创建一个新的节点
    if (!head || (reverse ? head->val >= node->val : head->val <= node->val)) {
        // 如果链表为空或插入的节点值小于等于链表头节点的值（如果reverse为true则判断大于等于）
        node->next = head; // 将新节点的指针指向链表头节点
        head = node; // 更新链表头节点的指针为新节点
    } else {
        ListNode<T> *cur = head; // 遍历链表的指针
        while (cur->next && (reverse ? cur->next->val < node->val : cur->next->val > node->val)) {
            // 遍历链表直到找到插入位置（如果reverse为true则判断大于）
            cur = cur->next; // 移动到下一个节点
        }
        node->next = cur->next; // 将新节点的指针指向当前节点的下一个节点
        cur->next = node; // 将当前节点的指针指向新节点
    }
}

int main() {
    LinkedList<int> listA; // 创建一个整型链表对象listA
    LinkedList<int> listB; // 创建一个整型链表对象listB

    std::cout << "Enter 5 unordered integers for list A: ";
    for (int i = 0; i < 5; ++i) {
        int num;
        std::cin >> num;
        listA.insert(num, true); // 将输入的整数插入到listA中，按递减顺序插入
    }

    std::cout << "Enter 5 unordered integers for list B: ";
    for (int i = 0; i < 5; ++i) {
        int num;
        std::cin >> num;
        listB.insert(num); // 将输入的整数插入到listB中，按递增顺序插入
    }

    std::cout << "List A: ";
    listA.print(); // 打印listA

    std::cout << "List B: ";
    listB.print(); // 打印listB

    LinkedList<int> intersection = listA.intersection(listB); // 求listA和listB的交集
    std::cout << "Intersection: ";
    intersection.print(); // 打印交集

    LinkedList<int> unionList = listA.unionList(listB); // 求listA和listB的并集
    std::cout << "Union: ";
    unionList.print(); // 打印并集

    listB.reverse(); // 反转listB
    std::cout << "Reversed list B: ";
    listB.print(); // 打印反转后的listB

    LinkedList<int> merged = listA.merge(listB); // 合并listA和listB
    std::cout << "Merged list: ";
    merged.print(); // 打印合并后的链表

    LinkedList<int> duplicated = merged.duplicate(); // 复制合并后的链表
    std::cout << "Duplicated list: ";
    duplicated.print(); // 打印复制后的链表

    return 0;
}
