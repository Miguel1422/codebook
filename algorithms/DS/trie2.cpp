// C++ implementation of search and insert
// operations on Trie
#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 26;

typedef struct trie {
    int nwords; // Number of nwords
    trie *child[ALPHABET_SIZE];

    trie() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            child[i] = nullptr;
        }
        nwords = 0;
    }

    int gid(const char &i) {
        return i - 'a'; // Only lowercase
    }

    void insert(const string &word, int index = 0) {
        if (index == word.length()) {
            nwords++;
            return;
        }
        int id = gid(word[index]);

        if (child[id] == nullptr) {
            child[id] = new trie;
        }
        child[id]->insert(word, index + 1);
    }

    // Return how many nwords are inserted
    int words(const string &word, int index = 0) {
        if (index == word.length()) return nwords;
        int id = gid(word[index]);
        if (child[id] == nullptr) {
            return 0;
        }
        return child[id]->words(word, index + 1);
    }

    ~trie() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            delete child[i];
        }
    }

} Trie;

void generate(Trie &t, string word = "") {
    t.insert(word);
    if (word.length() == 5) {
        return;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        generate(t, word + c);
    }
}

int main() {
    Trie t;
    generate(t);
    t.insert("hola");
    t.insert("hola");
    cout << "Done";
    string s;
    while(cin >> s) {
        cout << t.words(s) << "\n";
    }
    return 0;
}