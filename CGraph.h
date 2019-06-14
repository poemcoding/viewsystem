#pragma once
#include<iostream>
#include <fstream>
#define MAX_VERTEX_NUM 20	//��󶥵���
	
#define MAX_NAME_LEN 20		//�������Ƴ���
#define MAX_DESC_LEN 100	//������ܳ���
//int nSpotCount;
using namespace std;
typedef struct Path
{
	int vexs[MAX_VERTEX_NUM];//����һ��·��
	Path* next;//��һ��·��
}*PathList;
struct Vex
{
	int num;//���
	char name[MAX_NAME_LEN];//����
	char desc[MAX_DESC_LEN];//����
};

struct Edge
{
	int vex1;//��һ��������
	int vex2;//�ڶ���������
	int weight;
};
class CGraph
{
private:
	int m_aAdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�ڽӾ���
	Vex m_aVexs[MAX_VERTEX_NUM];//��������
	int m_nVexNum=0;//��ǰ����
	int nSpotCount;//�ڵ���Ŀ
//	void DFS(int nVex, bool aVisited[], int& nIndex, PathList &List);//�����������
public:
	void Init(void);//��ʼ��ͼ�ṹ
	bool InsertVex(Vex sVex);//��Ӷ���
	bool InsertEdge(Edge sEdge);//����ߵ��ڽ�����
	Vex GetVex(int nVex);//��ѯ����
	int GetWeight(int nIndex, int j);//��ȡ�ߵ�Ȩֵ
	int FindEdge(int nVex, Edge aEdge[]);//��ѯ��ָ�����������ı�
	void SetnSpotCount(int num);
	int GetVexNum(void);//��ȡ��ǰ������
	int GetnSpotCount(void);//��ȡ��������
//	void DFSTraverse(int nVex, PathList& List);//��ñ������
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);//��Ѱ���·��
	int FindMinTree(Edge aPath[]);//������С������
	void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList);//ʹ���������������������ͼ
	void DFSTraverse(int nVex, PathList& pList);//����DFS()�������õ���������������
	CGraph();
	~CGraph();
};



