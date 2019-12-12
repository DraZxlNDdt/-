#include<cstdio>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#include<map>
#include<bitset>
#define J setw(5)
using namespace std;

const int N = 5005;
bitset<N>f[N];
int n;
int main () {
    fstream fin("a.in", ios::in), fout("a.out", ios::out);
    fin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0, k; j < n; ++j) fin >> k, f[i][j] = k;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if(f[j][i]) f[j] |= f[i];
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) fout << (f[i][j] ? 1 : 0) << (j==n-1 ? "\n" : " ");
    return 0;
}