#ifndef __LP_SOLVER_H__
#define __LP_SOLVER_H__

#include "common.h"


int* lp_solver(int sid,int eid,int edge_num,struct edge edge_set[MAX_EDGE_NUM],int node_num,bool is_must_node[MAX_NODE_NUM],int &cnt,int ans[],vector<int> node_next[MAX_NODE_NUM]);


#endif // LP_SOLVER
