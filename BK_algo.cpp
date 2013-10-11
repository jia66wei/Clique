#include<iostream>
#include<set>
#include<algorithm>
#include<map>
#include<fstream>

using namespace std;
/*
 * http://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 * */
#define threshold 2500  //三元组个数阈值

typedef map<string, set<string> >  M;
typedef set<string>S;

void Traverse(S s,string uid)
{
	cout << uid << "\t";
	int size = s.size() ,n = 0;
	for(S::iterator it = s.begin();it != s.end(); ++it)
	{
		cout <<*it ;
		if( n <  size)
			cout << "\t";
		++n;
	}
	cout << endl;
}


void BK(string uid,set<string>A,set<string>nodes, M Hufen, S node_old)
{
	//cout <<"BK beginning\n";
	if(nodes.size() == 0 && node_old.size() == 0)
	{
		Traverse(A,uid);
	}
	else
	{
		set<string>T = nodes;
		S old = node_old;
		for(set<string>::iterator iter=nodes.begin(); iter != nodes.end(); ++iter)
		{
			A.insert(*iter);
			set<string>inter;
			set<string>node_flag;
			set_intersection(Hufen[*iter].begin(),Hufen[*iter].end(),T.begin(),T.end(),inserter(inter,inter.begin()));
			set_intersection(Hufen[*iter].begin(),Hufen[*iter].end(),old.begin(),old.end(),inserter(node_flag,node_flag.begin()));
			BK(uid,A,inter,Hufen,node_flag);
			T.erase(*iter);
			A.erase(*iter);
			old.insert(*iter);
		}
	}

}

void ReadFile(char *infile)
{
	ifstream in(infile);
	string buffer, flag("");
	M Hufen;
	S node;
	int num = 0;
	while(getline(in,buffer))
	{
		int pos1 =  buffer.find("\t");
	    int pos2 = 	buffer.rfind("\t");
		string uid = buffer.substr(0,pos1);
		string fan1 = buffer.substr(pos1+1,pos2-pos1-1);
		string fan2 = buffer.substr(pos2+1,buffer.length()-pos2-1);
		//cout << uid<<"|"<<fan1<<"|"<<fan2 << endl;
		if(flag == uid)
		{
			++num;
			node.insert(fan1);
			node.insert(fan2);
			if(Hufen.find(fan1) != Hufen.end())
			{
				set<string>s;
				Hufen.insert(make_pair(fan1,s));
			}
			if(Hufen.find(fan2) != Hufen.end())
			{
				set<string>s;
				Hufen.insert(make_pair(fan2,s));
			}
			Hufen[fan1].insert(fan2);
			Hufen[fan2].insert(fan1);
		}
		else
		{
			if( ""!= flag && num < threshold)
			{
				S A;
				S node_old; // already get 
				cout << "the clique of " << flag << " is: \n";
				BK(flag,A,node,Hufen,node_old);
			}
			node.clear();
			Hufen.clear();
			num = 0;
			flag = uid;
			set<string>s1,s2;
			Hufen.insert(make_pair(fan1,s1));
			Hufen.insert(make_pair(fan2,s2));
			Hufen[fan1].insert(fan2);
			Hufen[fan2].insert(fan1);
			node.insert(fan1);
			node.insert(fan2);
		}

	}
	//the last uid
	if(num < threshold)
	{
		S A;
		S node_old; // already get 
		cout << "the clique of " << flag << " is: \n";
		BK(flag,A,node,Hufen,node_old);
	}
	
}

int main(int argc, char * argv[])
{
	if(argc <2)
	{
		cout << "nedd hufen file(sanyuanzu)" << endl;
	}
	ReadFile(argv[1]);	  

}





