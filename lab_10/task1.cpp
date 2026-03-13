#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <locale>

using namespace std;

struct Node {
    wchar_t ch;
    int freq;
    Node* left;
    Node* right;

    Node(wchar_t c, int f) {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }

    Node(Node* l, Node* r) {
        ch = L'\0';
        freq = l->freq + r->freq;
        left = l;
        right = r;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, wstring code, map<wchar_t, wstring>& huffmanCode) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        if (code == L"") code = L"0";
        huffmanCode[root->ch] = code;
    }

    buildCodes(root->left, code + L"0", huffmanCode);
    buildCodes(root->right, code + L"1", huffmanCode);
}

Node* buildHuffmanTree(const wstring& text) {
    map<wchar_t, int> freq;

    for (size_t i = 0; i < text.length(); i++) {
        freq[text[i]]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (map<wchar_t, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        pq.push(new Node(it->first, it->second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(left, right);
        pq.push(parent);
    }

    return pq.top();
}

wstring encode(const wstring& text, map<wchar_t, wstring>& huffmanCode) {
    wstring encoded = L"";

    for (size_t i = 0; i < text.length(); i++) {
        encoded += huffmanCode[text[i]];
    }

    return encoded;
}

wstring decode(Node* root, const wstring& encodedText) {
    wstring decoded = L"";
    Node* current = root;

    for (size_t i = 0; i < encodedText.length(); i++) {
        if (encodedText[i] == L'0')
            current = current->left;
        else
            current = current->right;

        if (current->left == NULL && current->right == NULL) {
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

void printCodes(map<wchar_t, wstring>& huffmanCode) {
    wcout << L"Таблиця кодів Ґаффмена:\n";
    for (map<wchar_t, wstring>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it) {
        if (it->first == L' ')
            wcout << L"' ' : " << it->second << endl;
        else
            wcout << it->first << L" : " << it->second << endl;
    }
}

int main() {
    locale::global(locale(""));
    wcout.imbue(locale());
    wifstream fin("input.txt");
    fin.imbue(locale());

    if (!fin.is_open()) {
        wcout << L"Помилка відкриття файлу input.txt\n";
        return 1;
    }

    wstring text, line;
    while (getline(fin, line)) {
        text += line;
    }
    fin.close();

    if (text.empty()) {
        wcout << L"Файл порожній.\n";
        return 1;
    }

    Node* root = buildHuffmanTree(text);

    map<wchar_t, wstring> huffmanCode;
    buildCodes(root, L"", huffmanCode);

    printCodes(huffmanCode);

    wstring encodedText = encode(text, huffmanCode);
    wcout << L"\nПочатковий текст:\n" << text << endl;
    wcout << L"\nЗакодований текст:\n" << encodedText << endl;

    wofstream foutEncoded("encoded.txt");
    foutEncoded.imbue(locale());
    foutEncoded << encodedText;
    foutEncoded.close();

    wstring decodedText = decode(root, encodedText);
    wcout << L"\nДекодований текст:\n" << decodedText << endl;

    wofstream foutDecoded("decoded.txt");
    foutDecoded.imbue(locale());
    foutDecoded << decodedText;
    foutDecoded.close();

    return 0;
}