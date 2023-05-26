#include<bits/stdc++.h>
#include "set_rank.h"
using namespace std;
    string setrank::binary_to_string(string s)
    {
        int n=0;
        for(int i=6;i>=0;i--)
        {
            if(s[i]=='1') n+=pow(2,6-i);
        }
        string feedback="";
        feedback+=(char)n;
        return feedback;
    }
    long long setrank::binary_to_longlong(string s)
    {
        long long n=0;
        for(int i=(int)s.length();i>=0;i--)
        {
            if(s[i]=='1') n+=pow(2,(int)s.length()-i-1);
        }
        return n;
    }
    string setrank::string_to_binary(string s)
    {
        string feedback="";
        for(int i=0;i<s.length();i++)
        {
            string addstring="";
            int n=(int)s[i];
            for(int i=0;i<=6;i++)
            {
                addstring+=(char)((int)'0'+(n%2));
                n/=2;
            }
            reverse(addstring.begin(),addstring.end());
            feedback+=addstring;
        }
        return feedback;
    }
    string setrank::longlong_to_binary(long long n)
    {
        if(n==0) return "0";
        string feedback="";
        while(n>0)
        {
            feedback+=(char)((int)'0'+(n%2));
            n/=2;
        }
        reverse(feedback.begin(),feedback.end());
        return feedback;
    }
    setrank::setrank()
    {
        //read
        vector<pair<string,long long>> feedback;
        vector<string> data;
        ifstream ifs("rank.txt", std::ios::in);
        if (!ifs.is_open()) {
            cout << "Failed to open file.\n";
            return;
        }
        string s;
        while (getline(ifs, s)) {
            data.push_back(s);
        }
        if(data.size()==1) v={};
        string name="";
        for(int i=0;i<data.size();i++)
        {
            if(i%2==0)
            {
                name="";
                for(int j=0;j<data[i].length();j=j+7)
                {
                    name+=binary_to_string(data[i].substr(j,7));
                }
            }
            else
            {
                feedback.push_back({name,binary_to_longlong(data[i])});
            }
        }
        ifs.close();
        v=feedback;
    }
    pair<int,long long> setrank::renewrank(pair<string,long long> p)
    {
        int idx=-1;
        for(int i=0;i<v.size();i++)
        {
            if(v[i].first==p.first)
            {
                idx=i;
                break;
            }
        }
        if(idx==-1)
        {
            v.push_back(p);
        }
        else
        {
            v[idx].second=max(v[idx].second,p.second);
        }
        sort(v.begin(),v.end(),[](pair<string,long long> a,pair<string,long long> b)
        {
            if(a.second==b.second) return a.first<b.first;
            return a.second>b.second;
        });
        idx=-1;
        for(int i=0;i<v.size();i++)
        {
            if(v[i].first==p.first)
            {
                idx=i;
                break;
            }
        }
        //write in
        ofstream ofs;
        ofs.open("rank.txt");
        if (!ofs.is_open()) {
            cout << "Failed to open file.\n";
            return {};
        }
        for (int i = 0; i < v.size(); i++) {
            ofs << string_to_binary(v[i].first) << "\n" << longlong_to_binary(v[i].second);
            if(i<v.size()-1) ofs << "\n";
        }
        ofs.close();
        return {idx+1,v[idx].second};
    }