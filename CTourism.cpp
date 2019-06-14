#include "CTourism.h"
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define VEX_FILE_NAME "Vex.txt"
#define EDGE_FILE_NAME "Edge.txt"


void CTourism::CreateGraph(void)
{
	int IndexNum;//顶点数目
	cout << "=====create the scene graph=====" << endl;
	m_Graph.Init();
	fstream vex;
	vex.open("D:\\文件资源\\学习生活\\代码\\数据结构实验\\GraphCPro\\GraphCPro\\Vex.txt");
	vex >> IndexNum;
	m_Graph.SetnSpotCount(IndexNum);
	cout << "the number of vex" << m_Graph.GetnSpotCount() << endl;
	cout << "----vex----" << endl;
	Vex sVex;
	
	for (int i = 0; i < m_Graph.GetnSpotCount(); i++)
	{
		vex >> sVex.num;
		vex >> sVex.name;
		vex >> sVex.desc;
		cout << sVex.num << "-" << sVex.name << endl;
		if (!m_Graph.InsertVex(sVex)) 
		{
			cout << "insert vex error";
			continue;
		}
	}
	vex.close();
	//设置图的边
	fstream pEdge;
	pEdge.open("D:\\文件资源\\学习生活\\代码\\数据结构实验\\GraphCPro\\GraphCPro\\Edge.txt");
	cout << "-----edge-----"<<endl;
	Edge sEdge;
	for (int i = 0; i < 10; i++)
	{
		pEdge >> sEdge.vex1;
		pEdge >> sEdge.vex2;
		pEdge >> sEdge.weight;
		cout << "<v" <<sEdge.vex1 << "," << "v"<<sEdge.vex2 << ">  "<<sEdge.weight <<endl;
		if (!m_Graph.InsertEdge(sEdge))
		{
			cout << "insert edge error";
			continue;
		}
	}
	
	pEdge.close();
}
CTourism::CTourism()
{
}
void CTourism::GetSpotInfo()
{
	int iNum;
	cout << "=====search spot information=====" << endl;
	for (int i = 0; i < m_Graph.GetnSpotCount(); i++)
	{
		cout << m_Graph.GetVex(i).num << "-" << m_Graph.GetVex(i).name << endl;
	}
	cout << "please enter the number of spot which you want to query:";
	cin >> iNum;
	cout << m_Graph.GetVex(iNum).name << endl << m_Graph.GetVex(iNum).desc<<endl;
	cout<<"------scenes around------\n";
	for (int i = 0; i < m_Graph.GetnSpotCount(); i++) {
		if (m_Graph.GetWeight(iNum,i) != 0) {//i为循环的列数
			printf("%s->%s  %dm\n", m_Graph.GetVex(iNum).name, m_Graph.GetVex(i).name, m_Graph.GetWeight(iNum, i));
		}
	}
}

void CTourism::TravelPath()
{
	cout << "====the Spot Navigation====" << endl;
	int nVexNum = m_Graph.GetnSpotCount();//获取景点数目

	for (int i = 0; i < nVexNum; i++)//显示景点编号名称
	{
		Vex sVex = m_Graph.GetVex(i);
		cout << sVex.num << "-" << sVex.name << endl;
	}
	int nVex;//查询景点号
	cout << "enter the number of spot:";
	cin >> nVex;
	if (nVex < 0 || nVex >= m_Graph.GetnSpotCount())
	{
		cout << "error!" << endl;
		return;
	}
	//查询从nvex开始的旅游路线
	PathList pList = (PathList)malloc(sizeof(Path));
	PathList phead = pList;
	//查询导航路线
	
	m_Graph.DFSTraverse(nVex, pList);

	//输出路线

	int k = 1;

	pList = phead;
	
	while (pList->next)
	{
		Vex sVex = m_Graph.GetVex(pList->vexs[0]);//输出一条路线
		cout << "route " << k++ << ":" << sVex.name;  //输出起点
		for (int j = 1; j < nVexNum; j++)
		{
			sVex = m_Graph.GetVex(pList->vexs[j]); //输出后面N个顶点
			cout << "->" << sVex.name;
		}
		cout << endl;
		Path* temp = pList;
		pList = pList->next;
		free(temp); //释放空间
	}
	
}

void CTourism::FindShortPath(void)
{
	cout << "====Search The Shortest Route====" << endl;
	int nVexNum = m_Graph.GetnSpotCount();
	
	for (int i = 0; i < nVexNum; i++)
	{
		Vex sVex = m_Graph.GetVex(i);   //列出景点信息
		cout << sVex.num << "-" << sVex.name << endl;
	}
	int nVexStart;
	int nVexEnd;
	cout << "enter the entrance number: ";
	cin >> nVexStart;
	cout << "enter the exit number: ";
	cin >> nVexEnd;
	//cout << nVexNum;

	if (nVexStart < 0 || nVexStart >= nVexNum || nVexEnd < 0 || nVexEnd >= nVexNum)
	{
		cout << "error input！" << endl;
		return;
	}
	Edge aPath[MAX_VERTEX_NUM];
	int nNum = m_Graph.FindShortPath(nVexStart, nVexEnd, aPath);
	Vex sVex = m_Graph.GetVex(aPath[0].vex1);
	int nLength = 0;
	Vex vexstart = m_Graph.GetVex(nVexStart);
	cout << "the shortest route is： " << vexstart.name;
	for (int i = 0; i < nNum; i++)
	{
		sVex = m_Graph.GetVex(aPath[i].vex2);
		cout << "-" << sVex.name;
		nLength += aPath[i].weight;
	}
	cout << endl;
	cout << "the shortest length is： " << nLength << endl;
	
}
void CTourism::DesignPath(void)
{
	cout << "design the circuit:" << endl;
	cout << "--------circuit design--------" << endl;
	Edge aPath[20];
	m_Graph.FindMinTree(aPath); //得到规划路线
	
	if (m_Graph.GetnSpotCount() == 0)
	{
		cout << "please create graphic first! " << endl;
		return;
	}
	int nAllLength = 0;
	cout << "design circuit between： " << endl;
	for (int i = 0; i < m_Graph.GetnSpotCount() - 1; i++)
	{
		Vex sVex1 = m_Graph.GetVex(aPath[i].vex1);
		Vex sVex2 = m_Graph.GetVex(aPath[i].vex2);
		cout << sVex1.name << "-" << sVex2.name << "  " << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "the total length of circuit：" << nAllLength << "m" << endl;
}
void CTourism::ShowMenu()
{
	int iMenuChoice=1;
	while (!(iMenuChoice <= 0 || iMenuChoice > 5))
	{
		cout << "=====Scenic Spot Administration System=====" << endl;
		cout << "1.create scenic spot graph" << endl;
		cout << "2.search spot information" << endl;
		cout << "3.scenic spot navigation" << endl;
		cout << "4.search the shortest course" << endl;
		cout << "5.Laying Circuit Planning" << endl;
		cout << "0.exit" << endl;
		cout << "please enter your choice(0-5):";
		cin >> iMenuChoice;
		CTourism tour;
		switch (iMenuChoice)
		{
		case 0:exit(0);
		case 1: {tour.CreateGraph(); break; }
		case 2: {tour.GetSpotInfo(); break; }
		case 3: {tour.TravelPath(); break; }
		case 4:{tour.FindShortPath();break;}
		case 5:{tour.DesignPath();break;}
			break;
		}
	}
}
CTourism::~CTourism()
{
}
