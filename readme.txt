*************************************************************************
1. 参考网址： http://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
2. 输入数据： input.txt   格式： 3元组，两两互粉
3. 运行： ./BK_algo   input.txt
版本更新：
4. BK_algo_1.cpp: #输出的顺序性还是不能满足
   4.1 为了保持数据进栈出栈的有效性，将BK函数中的 A变量 用vector 替换掉set
   4.2 添加圈子个数统计
  
5. Clique_BK.c:
   5.1 基于以前版本速度慢，特地实现了C版本， 没有每个USER圈子数目的统计

python算法包---networkx:
6. Clique_nx.py:
   6.1 示例算法
   6.2 从屏幕输入数据 python2.6 Clique_nx.py  < input.txt
   6.3 Clique_nx.py : 添加了三元组数目限制
7.
	created by 20160429   
    
*************************************************************************
