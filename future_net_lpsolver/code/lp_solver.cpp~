#include "lp_solver.h"


vector< vector<int> > cir_set;
vector< vector<int> > load_set;

bool dfs_find_cir(int u,vector<int> node_next[MAX_NODE_NUM],double k[],bool tag[],vector<int> &tmp,struct edge edge_set[MAX_EDGE_NUM])
{
	if(tag[u])
	{
		return true;
	}
	tag[u] = true;

	for(int i=0;i<node_next[u].size();i++)
		if(k[node_next[u][i]] > 0)
		{
			tmp.push_back(node_next[u][i]);
			return dfs_find_cir(edge_set[node_next[u][i]].r,node_next,k,tag,tmp,edge_set);
		}
	return false;
}


int find_cir(int sid,int eid,int node_num,double k[],struct edge edge_set[MAX_EDGE_NUM],vector<int> node_next[MAX_NODE_NUM],vector<int> &ans)
{
	
	bool tag[MAX_NODE_NUM] = {0};
	vector<int> tmp;
	int cnt = 0;	
	if(dfs_find_cir(sid,node_next,k,tag,tmp,edge_set))
	{
		cnt++;
		cir_set.push_back(tmp);
	}
	ans = tmp;
	for(int i=0;i<node_num;i++)
		if(!tag[i])
		{
			vector<int> t_tmp;
			if(dfs_find_cir(i,node_next,k,tag,t_tmp,edge_set))
			{
				cnt++;
				cir_set.push_back(t_tmp);
			}
		}
	if(cnt > 0)
	{
		load_set.push_back(tmp);
	}
	return cnt;
}

double k[MAX_EDGE_NUM];
int ids[MAX_EDGE_NUM];
bool e_tag[MAX_EDGE_NUM];
int top = 0;

int* lp_solver(int sid,int eid,int edge_num,struct edge edge_set[MAX_EDGE_NUM],int node_num,bool is_must_node[MAX_NODE_NUM],int &cnt,int ans[],vector<int> node_next[MAX_NODE_NUM])
{
	cout << "lp_solver(" << sid << "," << eid << ")" << endl; 
	// lp
	lprec *lp;
	if( (lp = make_lp(0,edge_num)) == NULL)
		cout << "make lp error" << endl;
	
	for(int j=0;j<node_num;j++)
	{
		
		if(j == sid)
		{
			//memset(k,0,sizeof(k));
			// out degree = 1
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].l == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			//if(!add_constraint(lp, k, EQ, 1))
			if(!add_constraintex(lp, top, k, ids, EQ, 1))
				cout << "add_constraint sid error" << endl;
			

			//print_constraints(lp,edge_num+1);
			// in degree = 0
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].r == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			if(!add_constraintex(lp, top, k, ids, EQ, 0))
				cout << "add_constraint sid error" << endl;
		}
		else if(j == eid)
		{

			// out degree = 0
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].l == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			//if(!add_constraint(lp, k, EQ, 1))
			if(!add_constraintex(lp, top, k, ids, EQ, 0))
				cout << "add_constraint sid error" << endl;
			
			// in degree = 1
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].r == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			if(!add_constraintex(lp, top, k, ids, EQ, 1))
				cout << "add_constraint sid error" << endl;
		}
		else if(is_must_node[j])
		{

			// out degree = 1
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].l == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			//if(!add_constraint(lp, k, EQ, 1))
			if(!add_constraintex(lp, top, k, ids, EQ, 1))
				cout << "add_constraint sid error" << endl;
			
			// in degree = 1
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].r == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			if(!add_constraintex(lp, top, k, ids, EQ, 1))
				cout << "add_constraint sid error" << endl;

		}
		else 
		{

			// out degree = in degree
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].l == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
				else if(edge_set[i].r == j)
				{
					k[top] = -1;
					ids[top++] = i+1;
				}
			if(!add_constraintex(lp, top, k, ids, EQ, 0))
				cout << "add_constraint sid error" << endl;
			
			// Out degree <= 1
			top = 0;
			for(int i=0;i<edge_num;i++)
				if(edge_set[i].r == j)
				{
					k[top] = 1;
					ids[top++] = i+1;
				}
			if(!add_constraintex(lp, top, k, ids, LE, 1))
				cout << "add_constraint sid error" << endl;
		}
	}
	//print_lp(lp);
	//print_lp(lp);
	
	memset(e_tag,0,sizeof(e_tag));		
	for(int i=0;i<node_num;i++)
		for(int j=0;j<node_next[i].size();j++)
		{
			e_tag[node_next[i][j]] = true;

			int v = edge_set[node_next[i][j]].r;
			if(v < edge_set[node_next[i][j]].l)
				continue;
			top = 0;
			k[top] = 1;
			ids[top++] = node_next[i][j]+1;			
			for(int ii = 0;ii<node_next[v].size();ii++)
				if(edge_set[node_next[v][ii]].r == i)
				{
					k[top] = 1;
					ids[top++] = node_next[v][ii]+1;		
					if(!add_constraintex(lp, top, k, ids, LE, 1))
						cout << "add_constraint sid error" << endl;
					break;
				}
		}		

	// delect cir
	for(int i=0;i<cir_set.size();i++)
	{
		top = 0;
		for(int j=0;j<cir_set[i].size();j++)
		{
			k[top] = 1;
			ids[top++] = cir_set[i][j]+1;
		}
		if(!add_constraintex(lp, top, k, ids, LE, cir_set[i].size() - 1))
			cout << "add_constraint sid error" << endl;
	}
	
	
	// delect load
	for(int i=0;i<load_set.size();i++)
	{
		top = 0;
		for(int j=0;j<load_set[i].size();j++)
		{
			k[top] = 1;
			ids[top++] = load_set[i][j]+1;
		}
		if(!add_constraintex(lp, top, k, ids, LE, load_set[i].size() - 1))
			cout << "add_constraint sid error" << endl;
	}
		

	for(int i=0;i<edge_num;i++)
		k[i+1] = edge_set[i].cost;
	
	if(!set_obj_fn(lp,k))
		cout << "set_obj_fn error" << endl;

	for(int i=0;i<edge_num;i++)
	{
		set_lowbo(lp,i+1,0);
		if(e_tag[i])
			set_upbo(lp,i+1,1);
		else set_upbo(lp,i+1,0);
		set_int(lp,i+1,TRUE);
	}
	//cout<< "-----" << endl;
	//print_lp(lp);
	cout << "solve:" << solve(lp) << endl;
	//cout<< "++++++++++++" << endl;
	//print_solution(lp,1);
	//print_duals(lp);
	
	get_variables(lp,k);

	delete_lp(lp);

	//for(int i=0;i<edge_num;i++)
	//	cout << k[i] << " " <<edge_set[i].l << " " << edge_set[i].r << " " << edge_set[i].cost << endl;
	//getchar();
	//getchar();
	
	vector<int> tmp;
	if(find_cir(sid,eid,node_num,k,edge_set,node_next,tmp) > 0)
	{
		//cout << "find cir" << endl;
		lp_solver(sid,eid,edge_num,edge_set,node_num,is_must_node,cnt,ans,node_next);
	}
	else
	{
		cnt = tmp.size();
		cout << "cnt :" << cnt << endl;
		for(int i=0;i<cnt;i++)
		{
			ans[i] = tmp[i];
			//cout << tmp[i] << endl;		
		}
		
		//for(int i=0;i<edge_num;i++)
		//	cout << k[i] << " " <<edge_set[i].l << " " << edge_set[i].r << " " << edge_set[i].cost << " " <<edge_set[i].edge_id << endl;
	}
	
	// print res
	return NULL;
}
