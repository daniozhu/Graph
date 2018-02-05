#pragma once
#include <iostream>
#include <queue>

extern const unsigned int MAX_VERTEX_NUM;

template <class T>
struct Vertex
{ 
    Vertex() {}
    Vertex(const T& v) : Value(v) {}
	T			Value;

   // static Vertex Null;
};

//template<class T>
//Vertex<T> Vertex<T>::Null = Vertex<T>();

template<class T>
class Visitor
{
public:
	bool operator()(const Vertex<T>& vex);
};

template<class T>
inline bool Visitor<T>::operator()(const Vertex<T>& vex)
{
	std::cout << "Visiting vertx: " << vex.Value << std::endl;
	return true;
}

template<class T>
class Graph
{
public:
	Graph() 
        :m_vexnum(0), m_arcnum(0)
    {}
	virtual ~Graph() = default;

	// Get the position of the vertex, -1 not exist.
	int LocateVex(const Vertex<T>& vex) const;

    // Set vertex value
    void PutVex(const Vertex<T>& vex, const T& val);

	// Get vertex from index
    virtual const Vertex<T>* GetVex(int i) const = 0;

	// Get the first adjcent vertex of the given vex
	virtual const Vertex<T>* FirstAdjVex(const Vertex<T>& vex) const = 0;

	// Get next adjcent vertex of vex, relative to vexAdj
	virtual const Vertex<T>* NextAdjVex(const Vertex<T>& vex, const Vertex<T>& vexAdj) const = 0;

	// Insert an vertex without adding any arcs
	virtual void InsertVex(const Vertex<T>& vex) = 0;

	// Insert an arc between the two vertexs
	virtual void InsertArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo) = 0;

	// Delete the vertex and related arcs
	virtual void DeleteVex(const Vertex<T>& vex) = 0;

	// Delete an arc between the two vertexs
	virtual void DeleteArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo) = 0;

	// Depth-First search traverse the graph, start from vex and call Visitor() once for each vertex
	void DFSTraverse(const Vertex<T>& vex,  Visitor<T> visit);

	// Breadth-First Search traverse the graph, start from vex and call Visitor once for each vertex
	void BFSTraverse(const Vertex<T>& vex, Visitor<T> visit);

private:
    void DFS(const Vertex<T>& vex);
    void BFS(const Vertex<T>& vex);

protected:
    int                                 m_vexnum;
    int                                 m_arcnum;

private:

    Visitor<T>                    m_curVisitor;
    bool                             m_bVisited[MAX_VERTEX_NUM];

    // Used for Breadth-First Seach
    std::queue<int>           m_BFSqueue;  
};

template<class T>
void Graph<T>::DFSTraverse(const Vertex<T>& vex, Visitor<T> visit)
{
    // Reset flag and current visitor
    for (int i = 0; i < m_vexnum; ++i) m_bVisited[i] = false;
    m_curVisitor = visit;

    DFS(vex);
    for (int i = 0; i < m_vexnum; ++i)
    {
        if (!m_bVisited[i])  DFS(*GetVex(i));
    }
}

template<class T>
void Graph<T>::DFS(const Vertex<T>& vex)
{
    const int it = LocateVex(vex);
    if (it == -1) return;

    // Visit the vex
    if (!m_bVisited[it])
    {
        m_bVisited[it] = true;
        m_curVisitor(vex);
    }


    for (auto p = FirstAdjVex(vex); p != nullptr; p = NextAdjVex(vex, *p))
    {
        const int i = LocateVex(*p);
        if (!m_bVisited[i])
        {
            m_bVisited[i] = true;

            // Visit the adjacent vertex
            m_curVisitor(*p);

            // DFS from the vertex
            DFS(*p);
        }
    }
}

template<class T>
inline void Graph<T>::BFS(const Vertex<T>& vex)
{
    const int i = LocateVex(vex);
    if (i != -1 && !m_bVisited[i])
    {
        m_bVisited[i] = true;
        m_curVisitor(vex);
        m_BFSqueue.push(i);

        while (!m_BFSqueue.empty())
        {
            auto pV = GetVex(m_BFSqueue.front());
            m_BFSqueue.pop();

            for (auto p = FirstAdjVex(*pV); p != nullptr; p = NextAdjVex(*pV, *p))
            {
                const int k = LocateVex(*p);
                if (k != -1 && !m_bVisited[k])
                {
                    m_bVisited[k] = true;
                    m_curVisitor(*p);
                    m_BFSqueue.push(k);
                }
            }
        }
    }
}

template<class T>
void Graph<T>::BFSTraverse(const Vertex<T>& vex, Visitor<T> visit)
{
    //Rest visited array
    for (int i = 0; i < m_vexnum; ++i)
        m_bVisited[i] = false;

    m_curVisitor = visit;

    // Visit the start vex
    BFS(vex);

    // Visit other vertexs if there are not visited
    for (int j = 0; j < m_vexnum; ++j)
    {
        if (!m_bVisited[j])
            BFS(*GetVex(j));
    }
}

template<class T>
inline int Graph<T>::LocateVex(const Vertex<T>& vex) const
{
    for (int i = 0; i < m_vexnum; ++i)
    {
        if (GetVex(i)->Value == vex.Value)
            return i;
    }

    return -1;
}

template<class T>
inline void Graph<T>::PutVex(const Vertex<T>& vex, const T & val)
{
    int i = LocateVex(vex);
    auto pV = const_cast<Vertex<T>*>(GetVex(i));
    if (pV != nullptr)
        pV->Value = val;
}
