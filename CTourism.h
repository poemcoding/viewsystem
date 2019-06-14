#pragma once
#include "CGraph.h"
class CTourism
{
private:
	CGraph m_Graph;//CGraph对象
public:
	void ShowMenu();
	void CreateGraph(void);//读取文件创建景区图
	void GetSpotInfo(void);//查询指定顶点信息并显示相邻景点
	void TravelPath(void);//查询旅游景点导航
	void FindShortPath(void);//搜索两节点间最短路径
	void DesignPath(void);//查询铺设电路规划图
	CTourism();
	~CTourism();
};

