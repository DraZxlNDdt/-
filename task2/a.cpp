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

string s[N];
int t[N], n;
bool o;
int main () {
    fstream fin("a.in", ios::in), fout("a.out", ios::out);
    fin>>n; fout<<"by True:\n";
    for (int i = 0; i < n; ++i) fin>>s[i];
    for (int i = 0; i < (1<<n); ++i) fin>>t[i];
    for (int i = 0; i < (1<<n); ++i) if(t[i]) {
        if(o) fout<<"∨";
        else o=1;
        fout<<'(';
        for(int j = 0; j < n; ++j) {
            if(j) fout<<"∧";
            if(!(i>>j&1)) fout<<"┐";
            fout<<s[j];
        }
        fout<<')';
    }
    o = 0;
    fout<<"\nby False:\n";
    for (int i = 0; i < (1<<n); ++i) if(!t[i]) {
        if(o) fout<<"∧";
        else o=1;
        fout<<'(';
        for(int j = 0; j < n; ++j) {
            if(j) fout<<"∨";
            if(i>>j&1) fout<<"┐";
            fout<<s[j];
        }
        fout<<')';
    }
    fout<<'\n';
    return 0;
}