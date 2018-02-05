#pragma once
#include "Graph.h"

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
    VNode() :pfirstarc(nullptr) { }
    VNode(const Vertex<T>& v) : Vertex<T>(v), pfirstarc(nullptr) {}
    VNode(const T& v) : Vertex<T>(v), pfirstarc(nullptr) {}

	// Value is inherited from Vertex
	// T				Value 
	ArcNode*		pfirstarc;
};

template<class T>
class AdjListGraph : public Graph<T>
{
public:
	AdjListGraph();
	virtual ~AdjListGraph();

    // Get vertex from index
    virtual const Vertex<T>* GetVex(int i) const override;

    // Get the first adjcent vertex of the given vex
    virtual const Vertex<T>* FirstAdjVex(const Vertex<T>& vex) const override;

    // Get next adjcent vertex of vex, relative to vexAdj
    virtual const Vertex<T>* NextAdjVex(const Vertex<T>& vex, const Vertex<T>& vexAdj) const override;

    // Insert an vertex without adding any arcs
    virtual void InsertVex(const Vertex<T>& vex) override;

    // Insert an arc between the two vertexs
    virtual void InsertArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo) override;

    // Delete the vertex and related arcs
    virtual void DeleteVex(const Vertex<T>& vex) override;

    // Delete an arc between the two vertexs
    virtual void DeleteArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo) override;

private:
	VNode<T>	    m_vexs[MAX_VERTEX_NUM];
};


template<class T>
inline AdjListGraph<T>::AdjListGraph()
{
}

template<class T>
inline AdjListGraph<T>::~AdjListGraph()
{
}

template <class T>
inline const Vertex<T>* AdjListGraph<T>::GetVex(int i) const
{
    if (i < 0 || i > m_vexnum)
        return nullptr;

    return &m_vexs[i];
}

template<class T>
inline const Vertex<T>* AdjListGraph<T>::FirstAdjVex(const Vertex<T>& vex) const
{
    const int i = LocateVex(vex);
    if (i != -1)
    {
        ArcNode* p = m_vexs[i].pfirstarc;
        return  p==nullptr ? nullptr : &m_vexs[p->adjvex];
    }

    return nullptr;
}

template<class T>
inline const Vertex<T>* AdjListGraph<T>::NextAdjVex(const Vertex<T>& vex, const Vertex<T>& vexAdj) const
{
    const int i = LocateVex(vex);
    const int j = LocateVex(vexAdj);
    if (i != -1 && j != -1)
    {
        for (ArcNode* p = m_vexs[i].pfirstarc; p != nullptr; p = p->pnextarc)
        {
            if (p->adjvex == j)
                return p->pnextarc == nullptr ? nullptr : &m_vexs[p->pnextarc->adjvex];
        }
    }
    return nullptr;
}

template<class T>
inline void AdjListGraph<T>::InsertVex(const Vertex<T>& vex)
{
    m_vexs[m_vexnum++] = vex;
}

template<class T>
inline void AdjListGraph<T>::InsertArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo)
{
    int from = LocateVex(vexFrom);
    int to = LocateVex(vexTo);
    if (from != -1 && to != -1)
    {
        ArcNode* p = m_vexs[from].pfirstarc;
        while (p != nullptr && p->pnextarc != nullptr)
        {
            if (to == p->adjvex) // the arc is aleady existed
                return;

            p = p->pnextarc;
        }
 
        // Create arc node
        ArcNode* pArcNode = new ArcNode();
        pArcNode->adjvex = to;
        pArcNode->pnextarc = nullptr;
        pArcNode->weight = 0;

        m_vexs[from].pfirstarc == nullptr ? m_vexs[from].pfirstarc = pArcNode : p->pnextarc = pArcNode;
    }
}

template<class T>
inline void AdjListGraph<T>::DeleteVex(const Vertex<T>& vex)
{
    const int i = LocateVex(vex);
    if (i != -1)
    {
        ArcNode* p = m_vexs[i].pfirstarc;

        // delete arcs with vex as head
        while (p != nullptr)
        {
            ArcNode* pt = p->pnextarc;
            delete p;
            p = pt;
        }

        // delete arcs with vex as tail
        for (int j = 0; j < m_vexnum; ++j)
        {
            if (j == i) continue;

            ArcNode* pf = m_vexs[j].pfirstarc;
            if (pf == nullptr) continue;

            // the first arc connects to vertex that's being deleted
            if (pf->adjvex == i)
            {
                m_vexs[j].pfirstarc = pf->pnextarc;

                delete pf;
                continue;
            }

            // check second arc and so on.
            ArcNode* pPre = pf; 
            ArcNode* p = pf->pnextarc;
            while (pPre != nullptr && p != nullptr)
            {
                ArcNode* pt = p->pnextarc;
                if (p->adjvex == i)
                {
                    delete p;
                    pPre->pnextarc = pt;
                    break;
                }
                pPre = p;
                p = pt;
            }
        }

        // delete the vertex itself
        m_vexs[i].Value = "";
        m_vexs[i].pfirstarc = nullptr;

    }
}

template<class T>
inline void AdjListGraph<T>::DeleteArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo)
{
}
