#ifndef __COMMON_H__
#define __COMMON_H__

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
#include <queue>

using namespace std;

#define MAX_NODE_NUM 603
#define MAX_EDGE_NUM (MAX_NODE_NUM*8)

#define MP(a,b) make_pair(a,b)

#include "lib_record.h"
#include "lp_lib.h"

#if defined FORTIFY
#include "lp_fortify.h"

int EndOfPgr(int i)
{
    exit(i);
}
#endif

struct edge
{
    int edge_id;
    int l, r, old_l, old_r;
    int cost;
};

#endif
