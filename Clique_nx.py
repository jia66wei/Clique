#!/bin/python
import sys, pprint
sys.path.append('./networkx-1.8-py2.6.egg')
#pprint.pprint(sys.path)
import networkx as nx
def TraverseList(list):
	for i in range(len(list)-1):
		print list[i],"\t",
	print list[len(list)-1]

def TraverseClique(uid,cliques):
    print "The number of ",uid,"'s cliques is:", len(cliques)
    for i in range(0,len(cliques)):
		print uid,"\t",
		TraverseList(cliques[i])

G = nx.Graph()

'''
G.add_edge(2,1)
G.add_edge(2,3)
G.add_edge(2,4)
G.add_edge(2,5)
G.add_edge(3,4)
G.add_edge(1,5)
'''
(flag,uid,recip_uid) = (None,None,None)
Flag_uid=''
second_uid=''  
line = sys.stdin.readline()
while line:
	(flag,uid,recip_uid) = line.strip().split("\t");
	if(Flag_uid == ''):
		Flag_uid=flag
	if(Flag_uid == flag):
		G.add_edge(uid,recip_uid)
	else:
		Cliques = [c for c in nx.find_cliques(G)]
		TraverseClique(Flag_uid,Cliques)        
		G.clear()
		G = nx.Graph()
		Flag_uid = flag
		G.add_edge(uid,recip_uid)
	line = sys.stdin.readline()

Cliques = [c for c in nx.find_cliques(G)]
TraverseClique(Flag_uid,Cliques)        
#cliques = [c for c in nx.find_cliques(G)]
#TraverseClique(cliques)        
