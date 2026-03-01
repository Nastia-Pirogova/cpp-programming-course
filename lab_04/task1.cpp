#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Node {
    string key;
    string phone;
    Node *left;
    Node *right;

    Node(const string &k, const string &p)
        : key(k), phone(p), left(nullptr), right(nullptr) {
    }
};

class BST {
private:
    Node *root = nullptr;

    Node *minNode(Node *x) const {
        if (!x) return nullptr;
        while (x->left) x = x->left;
        return x;
    }

    Node *searchRec(Node *x, const string &k) const {
        if (!x || x->key == k) return x;
        if (k < x->key) return searchRec(x->left, k);
        return searchRec(x->right, k);
    }

    Node *insertRec(Node *x, const string &k, const string &phone) {
        if (!x) return new Node(k, phone);

        if (k < x->key) x->left = insertRec(x->left, k, phone);
        else if (k > x->key) x->right = insertRec(x->right, k, phone);
        else {
            x->phone = phone;
        }
        return x;
    }

    Node *deleteRec(Node *x, const string &k) {
        if (!x) return nullptr;

        if (k < x->key) {
            x->left = deleteRec(x->left, k);
        } else if (k > x->key) {
            x->right = deleteRec(x->right, k);
        } else {
            if (!x->left) {
                Node *r = x->right;
                delete x;
                return r;
            }
            if (!x->right) {
                Node *l = x->left;
                delete x;
                return l;
            }

            Node *succ = minNode(x->right);
            x->key = succ->key;
            x->phone = succ->phone;
            x->right = deleteRec(x->right, succ->key);
        }
        return x;
    }

    void inorderRec(Node *x) const {
        if (!x) return;
        inorderRec(x->left);
        cout << "  " << left << setw(25) << x->key << " -> " << x->phone << "\n";
        inorderRec(x->right);
    }

    void destroyRec(Node *x) {
        if (!x) return;
        destroyRec(x->left);
        destroyRec(x->right);
        delete x;
    }

public:
    ~BST() {
        destroyRec(root);
    }

    void insert(const string &k, const string &phone) {
        root = insertRec(root, k, phone);
    }

    Node *search(const string &k) const {
        return searchRec(root, k);
    }

    void remove(const string &k) {
        root = deleteRec(root, k);
    }

    void printInorder() const {
        cout << "Довідник (inorder, відсортовано за ключем):\n";
        inorderRec(root);
    }
};

int main() {
    BST phoneBook;

    phoneBook.insert("Арцаблюк Роман Володимирович", "+380501112233");
    phoneBook.insert("Бобошко Олександр Володимирович", "+380671234567");
    phoneBook.insert("Велігін Артем Олександрович", "+380931010101");
    phoneBook.insert("Гичка Дарина Михайлівна", "+380661998877");
    phoneBook.insert("Грищенко Богдан Андрійович", "+380990000111");

    cout << "=== ПІСЛЯ ВСТАВКИ (INSERT) ===\n";
    phoneBook.printInorder();

    cout << "\n=== ПОШУК (SEARCH) ===\n";
    string q1 = "Гичка Дарина Михайлівна";
    if (Node *found = phoneBook.search(q1)) {
        cout << "Знайдено: " << found->key << " -> " << found->phone << "\n";
    } else {
        cout << "Не знайдено: " << q1 << "\n";
    }

    string q2 = "Грищенко Богдан Андрійович";
    if (Node *found = phoneBook.search(q2)) {
        cout << "Знайдено: " << found->key << " -> " << found->phone << "\n";
    } else {
        cout << "Не знайдено: " << q2 << "\n";
    }

    cout << "\n=== ОНОВЛЕННЯ ТЕЛЕФОНУ (INSERT існуючого ключа) ===\n";
    phoneBook.insert("Гичка Дарина Михайлівна", "+380661111111");
    phoneBook.printInorder();

    cout << "\n=== ВИДАЛЕННЯ (DELETE) ===\n";
    cout << "Видаляємо: Велігін Артем Олександрович\n";
    phoneBook.remove("Велігін Артем Олександрович");
    phoneBook.printInorder();

    cout << "\nВидаляємо: Бобошко Олександр Володимирович\n";
    phoneBook.remove("Бобошко Олександр Володимирович");
    phoneBook.printInorder();

    return 0;
}
