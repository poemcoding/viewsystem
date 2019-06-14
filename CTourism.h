#pragma once
#include "CGraph.h"
class CTourism
{
private:
	CGraph m_Graph;//CGraph����
public:
	void ShowMenu();
	void CreateGraph(void);//��ȡ�ļ���������ͼ
	void GetSpotInfo(void);//��ѯָ��������Ϣ����ʾ���ھ���
	void TravelPath(void);//��ѯ���ξ��㵼��
	void FindShortPath(void);//�������ڵ�����·��
	void DesignPath(void);//��ѯ�����·�滮ͼ
	CTourism();
	~CTourism();
};

