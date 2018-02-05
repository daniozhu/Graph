#pragma once
#include "Graph.h"

#include <string>
#include <algorithm>

const unsigned int MAX_VERTEX_NUM = 20;

using VRType = int;
struct InfoType { std::string Info; };

struct ArcCell
{
public:
	ArcCell()
		:_adj(0), _pinfo(nullptr)
	{}

	VRType			_adj;				// 1 = adjcent, 0 = not adjcent;
	InfoType*			_pinfo;				// other info pointer about the arc
};

using AdjMatrix = ArcCell[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

template<class T>
class AdjMatrixDiGraph : public Graph<T>
{
public:
	AdjMatrixDiGraph();
	virtual ~AdjMatrixDiGraph();

    virtual const Vertex<T>* GetVex(int i) const override;
	virtual const Vertex<T>* FirstAdjVex(const Vertex<T>& vex) const override;
	virtual const Vertex<T>* NextAdjVex(const Vertex<T>& vex, const Vertex<T>& vexAdj) const override;
	virtual void InsertVex(const Vertex<T>& vex) override;
	virtual void InsertArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo) override;
	virtual void DeleteVex(const Vertex<T>& vex) override;
	virtual void DeleteArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo) override;

private:
	Vertex<T>					m_vexs[MAX_VERTEX_NUM];
	AdjMatrix						m_arcs;
};

/*
7.1 G1:
V1----------->V2
|/ \
|	   \
\|/	 \
V3---->V4

Adjcent matrix:
V1	V2	V3	V4
-------------------------
V1 |   0     1      1     0
V2 |   0	 0		 0		0
V3 |   0     0      0     1
V4 |   1     0      0     0
--------------------------
*/

template<class T>
inline AdjMatrixDiGraph<T>::AdjMatrixDiGraph()
{
}

template<class T>
inline AdjMatrixDiGraph<T>::~AdjMatrixDiGraph()
{
}

template<class T>
 const Vertex<T>* AdjMatrixDiGraph<T>::GetVex(int i) const
{
    if (i < 0 || i> m_vexnum)
        return nullptr;

    return &m_vexs[i];
}

template<class T>
const Vertex<T>* AdjMatrixDiGraph<T>::FirstAdjVex(const Vertex<T>& vex) const
{
	int i = LocateVex(vex);
	if (i != -1)
	{
		for (int j = 0; j < m_vexnum; ++j)
		{
			if (m_arcs[i][j]._adj == 1)
				return &m_vexs[j];
		}
	}

	return nullptr;
}

template<class T>

const Vertex<T>* AdjMatrixDiGraph<T>::NextAdjVex(const Vertex<T>& vex, const Vertex<T>& vexAdj) const
{
	int i = LocateVex(vex), j = LocateVex(vexAdj);
	if (i != -1 && j != -1)
	{
		for (int k = j+1; k < m_vexnum; ++k)
		{
			if (m_arcs[i][k]._adj == 1)
				return &m_vexs[k];
		}
	}

	return nullptr;
}

template<class T>
void AdjMatrixDiGraph<T>::InsertVex(const Vertex<T>& vex)
{
	m_vexs[m_vexnum++] = vex;
}

template<class T>
void AdjMatrixDiGraph<T>::InsertArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo)
{
	int i = LocateVex(vexFrom), j = LocateVex(vexTo);
	// invalid vertex location
	if (i == -1 || j == -1 || i > m_vexnum - 1 || j > m_vexnum-1)
		return;

	m_arcs[i][j]._adj = 1;
	m_arcnum++;
}

template<class T>
void AdjMatrixDiGraph<T>::DeleteVex(const Vertex<T>& vex)
{
	int i = LocateVex(vex);
	if (i != -1)
	{
		// Delete arcs connected to this vertex
		// step1: delete arcs start from and end with the vertex
		for (int j = 0; j < m_vexnum; ++j)
		{
			if (m_arcs[i][j]._adj == 1) {
				m_arcs[i][j]._adj = 0;
				m_arcs[i][j]._pinfo = nullptr;
				m_arcnum--;
			}

			if(m_arcs[j][i]._adj == 1) {
				m_arcs[j][i]._adj = 0;
				m_arcs[j][i]._pinfo = nullptr;
				m_arcnum--;
			}
		}

		// step2: delete the vertex itself
		m_vexs[i].Value = "";
	//	m_vexnum--; // the number of the vertex should NOT be changed otherwise all the index will be invalid
	}
}

template<class T>
void AdjMatrixDiGraph<T>::DeleteArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo)
{
	int i = LocateVex(vexFrom), j = LocateVex(vexTo);
	if (i != -1 && j != -1 && m_arcs[i][j]._adj == 1)
	{
		m_arcs[i][j]._adj = 0;
		m_arcs[i][j]._pinfo = nullptr;
		m_arcnum--;
	}
}

