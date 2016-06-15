#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "lib_record.h"
#include <stdio.h>
#include <time.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/time.h>

using namespace std;

#define MAX_NODE_NUM 603
#define MAX_EDGE_NUM (MAX_NODE_NUM*8)

#define MP(a,b) make_pair(a,b)
void search_route(char *graph[5000], int edge_num, char *condition);
int dfs(int now_id,bool inload[],int limit_load = 10000);

#endif
