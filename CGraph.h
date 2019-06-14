#pragma once
#include<iostream>
#include <fstream>
#define MAX_VERTEX_NUM 20	//最大顶点数
	
#define MAX_NAME_LEN 20		//景点名称长度
#define MAX_DESC_LEN 100	//景点介绍长度
//int nSpotCount;
using namespace std;
typedef struct Path
{
	int vexs[MAX_VERTEX_NUM];//保存一条路径
	Path* next;//下一条路径
}*PathList;
struct Vex
{
	int num;//编号
	char name[MAX_NAME_LEN];//名字
	char desc[MAX_DESC_LEN];//介绍
};

struct Edge
{
	int vex1;//第一个顶点编号
	int vex2;//第二个景点编号
	int weight;
};
class CGraph
{
private:
	int m_aAdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵
	Vex m_aVexs[MAX_VERTEX_NUM];//顶点数组
	int m_nVexNum=0;//当前顶点
	int nSpotCount;//节点数目
//	void DFS(int nVex, bool aVisited[], int& nIndex, PathList &List);//深度优先搜索
public:
	void Init(void);//初始化图结构
	bool InsertVex(Vex sVex);//添加顶点
	bool InsertEdge(Edge sEdge);//保存边到邻接数组
	Vex GetVex(int nVex);//查询顶点
	int GetWeight(int nIndex, int j);//获取边的权值
	int FindEdge(int nVex, Edge aEdge[]);//查询与指定顶点相连的边
	void SetnSpotCount(int num);
	int GetVexNum(void);//获取当前顶点编号
	int GetnSpotCount(void);//获取顶点总数
//	void DFSTraverse(int nVex, PathList& List);//获得遍历结果
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);//找寻最短路径
	int FindMinTree(Edge aPath[]);//构造最小生成树
	void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList);//使用深度优先搜索方法遍历图
	void DFSTraverse(int nVex, PathList& pList);//调用DFS()函数，得到深度优先搜索结果
	CGraph();
	~CGraph();
};



