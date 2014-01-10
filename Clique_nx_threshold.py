#!/bin/python
import sys, pprint
sys.path.append('./networkx-1.8-py2.6.egg')
#pprint.pprint(sys.path)
import networkx as nx

uid_not = open(sys.argv[1],'w')

def TraverseList(list):
	for i in range(len(list)-1):
		print list[i],"\t",
	print list[len(list)-1]
	del list[:]

def TraverseClique(uid,cliques):
    print  len(cliques)
    for i in range(0,len(cliques)):
		print uid,"\t",
		TraverseList(cliques[i])

G = nx.Graph()
threshold = 2500 # 
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
num = 0
line = sys.stdin.readline()
while line:
	(flag,uid,recip_uid) = line.strip().split("\x01");
	if(Flag_uid == ''):
		Flag_uid=flag
	if(Flag_uid == flag):
		G.add_edge(uid,recip_uid)
		num = num+1
	else:
		if(num < threshold):
			print "The number of ",Flag_uid,"'s cliques is:",
			Cliques = [c for c in nx.find_cliques(G)]
			TraverseClique(Flag_uid,Cliques)        
			del Cliques[:]
		else:
			uid_not.write(Flag_uid)
			uid_not.write("\n")
		num = 1
		G.clear()
		G = nx.Graph()
		Flag_uid = flag
		G.add_edge(uid,recip_uid)
	line = sys.stdin.readline()

if(num < threshold):
	Cliques = [c for c in nx.find_cliques(G)]
	TraverseClique(Flag_uid,Cliques)        
	del Cliques[:]
else:
	uid_not.write(Flag_uid)
	uid_not.write("\n")

uid_not.close()
#cliques = [c for c in nx.find_cliques(G)]
#TraverseClique(cliques)        
