/*
Searches for the string w in the string s (of length k). Returns the
0-based index of the first match (k if no match is found). Algorithm
runs in O(k) time.
*/

typedef vector<int> VI;

void buildTable(string &w, VI &t) {
    t = VI(w.length());
    int i = 2, j = 0;
    t[0] = -1;
    if (w.length() > 1) t[1] = 0;

    while (i < w.length()) {
        if (w[i - 1] == w[j]) {
            t[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0) j = t[j];
        else {
            t[i] = 0;
            i++;
        }
    }
}

int KMP(string &s, string &w) {
    int m = 0, i = 0;
    VI t;

    buildTable(w, t);
    while (m + i < s.length()) {
        if (w[i] == s[m + i]) {
            i++;
            if (i == w.length()) return m;
        } else {
            m += i - t[i];
            if (i > 0) i = t[i];
        }
    }
    return s.length();
}

//---------------------------- 2nd version
// Returns a vector containing the zero based index of
//  the start of each match of the string K in S.
//  Matches may overlap
//----------------------------
vector<int> KMP(string S, string K) {
    vector<int> T(K.size() + 1, -1);
    for (int i = 1; i <= K.size(); i++) {
        int pos = T[i - 1];
        while (pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
        T[i] = pos + 1;
    }

    vector<int> matches;
    for (int sp = 0, kp = 0; sp < s.size(); sp++) {
        while (kp != -1 && (kp == K.size() || K[kp] != S[sp]))
            kp = T[kp];
        kp++;
        if (kp == K.size()) matches.push_back(sp + 1 - K.size());
    }

    return matches;
}