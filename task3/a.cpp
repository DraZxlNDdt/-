#include<cstdio>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#include<map>
#define J setw(5)
using namespace std;

const int N = 5005;

map<string, int>id;
bool isflip[N];
int ls[N], rs[N], sy[N], t[N];
char fh[N];
string s, pr[N];

int S, z, rt, ns;

char yxj[4] = {'&', '|', '/', '*'};

bool isx (char x) {
    return x == '&' || x == '|' || x == '-' || x == '(' || x == ')' || x == '=' || x == '*' || x == '/';
}

int find (const string &s, int l, int r, char o) {
    /*int D = s.find(o, l);
    if (D > r) D = -1;
    return D;*/
    int d = 0;
    for (int i = l; i <= r; ++i) {
        if (s[i] == '(') ++d;
        else if (s[i] == ')') --d;
        else if (!d && o == s[i]) return i;
    }
    return -1;
}

int bt (const string &s, int l, int r, bool o) {
    int p, d;
    while(s[l] == '-') o^=1, ++l;
    if (s[l] == '(' && s.find(')', l) == r) {
        p = bt(s, l + 1, r - 1, 0);
        return isflip[p] = o, p;
    }
    p = ++ns;
    for (int i = 0; i < 4; ++i) if (d = find(s, l, r, yxj[i]), d != -1 && d < r) {
        ls[p] = bt(s, l, d - 1, o);
        rs[p] = bt(s, d + 1, r, 0);
        fh[p] = yxj[i];
        return p;
    }
    return sy[p] = id[s.substr(l, r-l+1)], isflip[p] = o, p;
}

bool dfs (int x) {
    if (!ls[x]) return (z>>sy[x]&1)^isflip[x];
    bool l = dfs(ls[x]), r = dfs(rs[x]), a;
    switch (fh[x]) {
        case '&': a = l & r; break;
        case '|': a = l | r; break;
        case '*': a = (l & r) || !(l | r); break;
        case '/': a = !l || r;
    }
    return a^isflip[x];
}

int main () {
    fstream fin("a.in", ios::in), fout("a.out", ios::out);
    if (!fin) return cout << "Sorry, a.in do not exist!\n", 0;
    for (int i = 0; i < 1; ++i) {
        fin >> s;
        int l = s.size();
        for (int j = 0, j2; j < l; j = j2 + 1) {
            for (j2 = j; j2 < l && !isx(s[j2]); ++j2) ;
            if (j2 == j) continue ;
            string t = s.substr(j, j2 - j);
            if (!id.count(t)) {
                pr[S++] = t;
                id[t] = stoi(t.substr(1, j2 - j - 1))-1;
            }
        }
    }
    rt = bt(s, 0, s.size()-1, 0);
    for (z = 0; z < (1<<S); ++z) t[z] = dfs(rt);
    fout << "化为主合取范式\n";
    bool o = 0;
    for (int i = 0; i < (1<<S); ++i) if(t[i]) {
        if(o) fout<<"∨";
        else o=1;
        fout<<'(';
        for(int j = 0; j < S; ++j) {
            if(j) fout<<"∧";
            if(!(i>>j&1)) fout<<"┐";
            fout<<pr[j];
        }
        fout<<')';
    }
    o = 0;
    fout<<"\n化为主析取范式\n";
    for (int i = 0; i < (1<<S); ++i) if(!t[i]) {
        if(o) fout<<"∧";
        else o=1;
        fout<<'(';
        for(int j = 0; j < S; ++j) {
            if(j) fout<<"∨";
            if(i>>j&1) fout<<"┐";
            fout<<pr[j];
        }
        fout<<')';
    }
    fout<<'\n';
    // for (auto a : id) fout << J << a.first << J << a.second << endl;
    // fin.close();
    // fout.close();
    return 0;
}