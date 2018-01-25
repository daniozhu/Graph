#pragma once
#include "Graph.h"

#include <string>

extern const unsigned int MAX_VERTEX_NUM;

struct ArcNode
{
	int				adjvex;
	ArcNode*		pnextarc;
	int				weight;
};

template<class T>
struct VNode : public Vertex<T>
{
	// Value is inherited from Vertex
	// T				Value 
	ArcNode*		pfirstarc;
};

template<class T>
class AdjListGraph 
{
public:
	AdjListGraph();
	virtual ~AdjListGraph();



private:
	VNode			m_vexs[MAX_VERTEX_NUM];
	int				m_vexnum;
	int				m_arcnum;
};


template<class T>
inline AdjListGraph<T>::AdjListGraph()
{
}

template<class T>
inline AdjListGraph<T>::~AdjListGraph()
{
}
