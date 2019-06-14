#include "CGraph.h"


void CGraph::Init(void)
{
	m_nVexNum = 0;
	for(int i=0;i<MAX_VERTEX_NUM;i++)
		for (int j = 0; j < MAX_VERTEX_NUM; j++) 
		{
			m_aAdjMatrix[i][j] = 0;
		}
}
bool CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM ) 
	{
		return false;//顶点已满
	}
	m_aVexs[m_nVexNum++] = sVex;
	return true;
}
bool CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= nSpotCount || sEdge.vex2 < 0||sEdge.vex2>=nSpotCount)//注意这里是最大景点数而不是文件中景点数，可能造成错误
	{
		return false;
	}
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}
Vex CGraph::GetVex(int v)
{
	return m_aVexs[v];
}
int CGraph::GetWeight(int nIndex, int j)
{
	return m_aAdjMatrix[nIndex][j];
}
int CGraph::FindEdge(int nvex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < nSpotCount; i++)
	{
		if (m_aAdjMatrix[nvex][i] != 0 && nvex != i)
		{
			aEdge[k].vex1 = nvex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[nvex][i];
			k++;
		}
	}
	return k;
}
int CGraph::GetVexNum(void)
{
	return m_nVexNum;
}

int CGraph::GetnSpotCount(void)
{
	return nSpotCount;
}

void CGraph::SetnSpotCount(int num)
{
	nSpotCount = num;
}
void CGraph::DFSTraverse(int nVex, PathList& pList)
{
	int nIndex = 0;
	bool aVisited[MAX_VERTEX_NUM] = { false };
	DFS(nVex, aVisited, nIndex, pList);

}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //保存最短路径
	int nShortDistance[MAX_VERTEX_NUM];             //保存最短距离
	bool aVisited[MAX_VERTEX_NUM];                  //判断某顶点是否已加入到最短路劲
	int v;

	for (v = 0; v < nSpotCount; v++)
	{
		aVisited[v] = false;
		if (m_aAdjMatrix[nVexStart][v] != 0)
		{
			nShortDistance[v] = m_aAdjMatrix[nVexStart][v];//初始化该顶点到其他顶点的距离，默认为两顶点间的距离
		}
		else
		{
			nShortDistance[v] = 0x7FFFFFFF;          //如果顶点v与nVexStart不相连，则最短距离设为最大值
		}
		nShortPath[v][0] = nVexStart;
		for (int w = 1; w < nSpotCount; w++)
		{
			nShortPath[v][w] = -1; //初始化最短路径
		}
	}

	aVisited[nVexStart] = true;
	int min;
	for (int i = 1; i < nSpotCount; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;       //判断是否还有顶点可以加入到集合中
		for (int w = 0; w < nSpotCount; w++)
		{
			if (!aVisited[w])
			{
				if (nShortDistance[w] < min && nShortDistance[w] < min)
				{
					v = w;                    //w顶点离nVexStart最近
					min = nShortDistance[w];  //w到nVexStart的最短距离为min
					bAdd = true;
				}
			}
		}
		if (!bAdd)  //如果没有顶点可以加入，则跳出循环
		{
			break;
		}
		aVisited[v] = true;
		nShortPath[v][i] = v;
		for (int w = 0; w < nSpotCount; w++)
		{
			if ((!aVisited[w]) && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_aAdjMatrix[v][w] > 0))
			{
				nShortDistance[w] = min + m_aAdjMatrix[v][w];//更新
				for (int i = 0; i < nSpotCount; i++)
				{
					nShortPath[w][i] = nShortPath[v][i];//如果w到顶点i的距离比较短，则将w的最短路径赋值给i
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
	for (int i = 1; i < nSpotCount; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}
int CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[MAX_VERTEX_NUM]; //判断某顶点是否在最小生成树顶点集合内
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		aVisited[i] = false;
	}
	aVisited[0] = true;   //0顶点加入到集合中
	int min;
	int nvex1, nvex2;

	for (int k = 0; k < nSpotCount - 1; k++)
	{
		min = 0xffff;
		for (int i = 0; i < nSpotCount; i++)
		{
			if (aVisited[i])   //从集合中取一个顶点
			{
				for (int j = 0; j < nSpotCount; j++)
				{
					if (!aVisited[j])
					{
						if ((m_aAdjMatrix[i][j] < min) && (m_aAdjMatrix[i][j] != 0))
						{
							nvex1 = i;
							nvex2 = j;
							min = m_aAdjMatrix[i][j];  //找出最短的边
						}
					}
				}
			}
		}
		aPath[k].vex1 = nvex1;
		aPath[k].vex2 = nvex2;  //保存最短路径的两个顶点
//		if (nvex1 != nvex2)
//		{ 
		aPath[k].weight = m_aAdjMatrix[nvex1][nvex2]; //将两个顶点加入到集合
		aVisited[nvex1] = true;
		aVisited[nvex2] = true;
		//}
	}
}
CGraph::CGraph()
{
}

void CGraph::DFS(int nvex2, bool aVisited[], int& nIndex, PathList& pList)//nIndex:访问路径的下标
{
	aVisited[nvex2] = true;
	pList->vexs[nIndex++] = nvex2;
	
	int nVexNum = 0;
	for (int i=0;i<nSpotCount;i++)
	{
		if (aVisited[i])	nVexNum++;
	}
	if (nVexNum == nSpotCount)
	{
		pList->next = (PathList)malloc(sizeof(Path));
		for (int i = 0; i < nSpotCount; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}
	else
	{
		for (int i = 0; i < nSpotCount; i++)//i
		{
			if ((!aVisited[i]) && (m_aAdjMatrix[nvex2][i] > 0))
			{
				DFS(i, aVisited, nIndex, pList);
				aVisited[i] = false;
				nIndex--;
			}
		}
	}
}

//int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
//{
//	//初始化
//	for (int i; i < MAX_VERTEX_NUM; i++)
//	{
//		
//	}
//}

CGraph::~CGraph()
{
}
