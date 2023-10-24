#include<iostream>
#include<string>

template<typename DataType>
struct Node {
    DataType data;
    Node<DataType> *next;
};

template<typename DataType>
class LinkList {
private:
    Node<DataType> *first;
public:
    LinkList();

    ~LinkList();

    void insert(DataType a, bool reverse = false);

    void printList();

    LinkList<DataType> *intersection(LinkList<DataType> &l);

    LinkList<DataType> *unionlist(LinkList<DataType> &l);

    void reverse();

    LinkList<DataType> *combine(LinkList<DataType> &l);

    LinkList<DataType> *duplicate();

    void removeduplicates();
};

template<typename DataType>
LinkList<DataType>::LinkList() {
    first = new Node<DataType>;
    first->next = nullptr;
}

template<typename DataType>
LinkList<DataType>::~LinkList() {
    Node<DataType> *p = first;
    while (first != nullptr) {
        first = first->next;
        delete p;
        p = first;
    }
}

template<typename DataType>
void LinkList<DataType>::insert(DataType a, bool reverse) {
    Node<DataType> *newNode = new Node<DataType>;
    newNode->data = a;

    if (reverse) {
        Node<DataType> *p = first;
        while (p->next != nullptr && p->next->data < a) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    } else {
        newNode->next = first->next;
        first->next = newNode;
    }
}

template<typename DataType>
void LinkList<DataType>::printList() {
    Node<DataType> *p = first->next;
    while (p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template<typename DataType>
LinkList<DataType> *LinkList<DataType>::intersection(LinkList<DataType> &l) {
    LinkList<DataType> *result = new LinkList<DataType>;

    Node<DataType> *p1 = first->next;
    Node<DataType> *p2 = l.first->next;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data == p2->data) {
            result->insert(p1->data);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->data < p2->data) {
            p1 = p1->next;
        } else {
            p2 = p2->next;
        }
    }

    return result;
}

template<typename DataType>
LinkList<DataType> *LinkList<DataType>::unionlist(LinkList<DataType> &l) {
    LinkList<DataType> *result = new LinkList<DataType>;

    Node<DataType> *p1 = first->next;
    Node<DataType> *p2 = l.first->next;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data == p2->data) {
            result->insert(p1->data);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->data < p2->data) {
            result->insert(p1->data);
            p1 = p1->next;
        } else {
            result->insert(p2->data);
            p2 = p2->next;
        }
    }

    while (p1 != nullptr) {
        result->insert(p1->data);
        p1 = p1->next;
    }

    while (p2 != nullptr) {
        result->insert(p2->data);
        p2 = p2->next;
    }

    return result;
}

template<typename DataType>
void LinkList<DataType>::reverse() {
    Node<DataType> *prev = nullptr;
    Node<DataType> *current = first->next;
    Node<DataType> *next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    first->next = prev;
}

template<typename DataType>
LinkList<DataType> *LinkList<DataType>::combine(LinkList<DataType> &l) {
    LinkList<DataType> *result = new LinkList<DataType>;

    Node<DataType> *p1 = first->next;
    Node<DataType> *p2 = l.first->next;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data >= p2->data) {
            result->insert(p1->data, true);
            p1 = p1->next;
        } else {
            result->insert(p2->data, true);
            p2 = p2->next;
        }
    }

    while (p1 != nullptr) {
        result->insert(p1->data, true);
        p1 = p1->next;
    }

    while (p2 != nullptr) {
        result->insert(p2->data, true);
        p2 = p2->next;
    }

    return result;
}

template<typename DataType>
LinkList<DataType> *LinkList<DataType>::duplicate() {
    LinkList<DataType> *result = new LinkList<DataType>;

    Node<DataType> *p = first->next;
    while (p != nullptr) {
        result->insert(p->data);
        result->insert(p->data);
        p = p->next;
    }

    return result;
}

int main() {
    LinkList<int> a;
    LinkList<int> b;

    // Insert 5 unordered integers into list a and sort in descending order
    std::cout << "Enter 5 integers for list a: ";
    for (int i = 0; i < 5; i++) {
        int num;
        std::cin >> num;
        a.insert(num, true);
    }

    // Insert 5 unordered integers into list b and sort in descending order
    std::cout << "Enter 5 integers for list b: ";
    for (int i = 0; i < 5; i++) {
        int num;
        std::cin >> num;
        b.insert(num);
    }

    // Print lists a and b
    std::cout << "List a: ";
    a.printList();
    std::cout << "List b: ";
    b.printList();

    // Find intersection of lists a and b
    LinkList<int> *intersectionList = a.intersection(b);
    std::cout << "Intersection: ";
    intersectionList->printList();

    // Find union of lists a and b
    LinkList<int> *unionList = a.unionlist(b);
    std::cout << "Union: ";
    unionList->printList();

    // Reverse list b
    b.reverse();
    std::cout << "Reversed list b: ";
    b.printList();

    // Combine lists a and b in descending order
    LinkList<int> *combinedList = a.combine(b);
    std::cout << "Combined list (descending order): ";
    combinedList->printList();

    // Duplicate combined list
    LinkList<int> *duplicatedList = combinedList->duplicate();
    std::cout << "Duplicated combined list: ";
    duplicatedList->printList();

    // Clean up memory
    delete intersectionList;
    delete unionList;
    delete combinedList;
    delete duplicatedList;

    return 0;
}
