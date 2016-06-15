#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#define INF 100000000
#define maxn 605
using namespace std;

typedef long long ll;

int adj[maxn][maxn];//邻接矩阵
int vis[maxn];
int n, m;//点的个数，边的个数
int start, target, must;

//最优路径节点序列
stack<int> shortest_path;
//最优路径长度
ll shortest_distance = INF;
//必经点集合
vector<int> mustpass;




void DFS(int cur, stack<int>& cur_path, ll cur_dis, int already_pass)
{
    vis[cur] = 1;
    cur_path.push(cur);
    if(find(mustpass.begin(), mustpass.end(), cur) != mustpass.end())already_pass += 1;
    if(cur == target && already_pass == must)
    {
        if(cur_dis < shortest_distance)
        {
            shortest_distance = cur_dis;
            shortest_path = cur_path;
            return;
        }
    }
    else if(cur == target && already_pass < must)return;
    else if(cur_dis >= shortest_distance)return;
    for(int i = 0; i < n; ++i)
    {
        if(adj[cur][i] < INF && !vis[i])
        {
            DFS(i, cur_path, cur_dis+adj[cur][i], already_pass);
            vis[i] = 0;
            cur_path.pop();
        }

    }
}



class Edge
{
public:
    int ei, es, et, ew;
    Edge() {};
    Edge(int i, int s, int t, int w):ei(i), es(s), et(t), ew(w) {};
};


inline int str2int(const string &string_temp)
{
    int int_temp = 0;
    stringstream stream(string_temp);
    stream>>int_temp;
    return int_temp;
}

vector<int> split(string str, char t)
{
    vector<int> vec;
    vector<int> num;
    int len = str.size();
    vec.push_back(-1);
    for(int i = 0; i < len; ++i)
    {
        if(str[i] == t)vec.push_back(i);
    }
    len = (int)vec.size();

    for(int i = 0; i < len; ++i)
    {
        num.push_back(str2int(str.substr(vec[i]+1, vec[i+1]-vec[i]+1)));
    }
    return num;
}



//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    vector<Edge> edge_set;
    vector<int> result;//最后的解
    //准备输入数据
    string str = demand;
    string mupa;
    string s_t;
    int tmp_len = str.size();
    int lastone = 0;
    for(int i = 0; i < tmp_len; ++i)
    {
        if(str[i] == ',')lastone = i;
    }
    s_t = str.substr(0, lastone);
    mupa = str.substr(lastone+1);
    vector<int> vec_st = split(s_t, ',');
    vector<int> vec_mupa = split(mupa, '|');

    //初始化邻接矩阵
    for(int i=0; i<=maxn; i++)
    {
        for(int j=0; j<=maxn; j++)
        {
            adj[i][j] = INF;
        }
    }
    set<int> point;
    int p = 0, x = 0, y = 0, w = 0;
    int input_index = 0;
    while(edge_num--)
    {
        vector<int> vec = split(topo[input_index++], ',');
        p = vec[0], x = vec[1], y = vec[2], w = vec[3];
        //记录有多少个点
        point.insert(x);
        point.insert(y);
        Edge e(p, x, y, w);
        edge_set.push_back(e);
        if(w < adj[x][y])//如果存在重边，取最小边
        {
            adj[x][y] = w;
        }
    }
    //有多少个点
    n = (int)point.size();
    point.clear();
    start = vec_st[0];
    target = vec_st[1];
    must = (int)vec_mupa.size();

    for(int i = 0; i < must; ++i)
    {
        mustpass.push_back(vec_mupa[i]);
    }
    stack<int> tmp;
    //cout<<start<<" "<<target<<endl;
    memset(vis, 0, sizeof(vis));
    DFS(start, tmp, 0, 0);
    vector<int> vec;
    //cout<<"len of shortest_path is "<<shortest_path.size()<<endl;
    while(!shortest_path.empty())
    {
        //cout<<shortest_path.top()<<" ";
        vec.push_back(shortest_path.top());
        shortest_path.pop();
    }
    //cout<<endl;
    cout<<"shortest_distance = "<<shortest_distance<<endl;
    reverse(vec.begin(), vec.end());
    vector<int> final_path;
    for(vector<int>::iterator iter = vec.begin(); iter != vec.end()-1; ++iter)
    {
        int pre = *iter;
        int next = *(iter+1);
        int mindis = INF;
        int index = -1;
        for(vector<Edge>::iterator it = edge_set.begin(); it != edge_set.end(); ++it)
        {
            if(pre == it->es && next == it->et)
            {
                if(it->ew < mindis)
                {
                    mindis = it->ew;
                    index = it->ei;
                }
            }
        }
        final_path.push_back(index);
    }

    cout<<"shortest path:"<<endl;
    for(vector<int>::iterator iter = final_path.begin(); iter != final_path.end(); ++iter)
    {
        cout<<*iter<<" ";
        record_result(*iter);
    }
    cout<<endl;
}








