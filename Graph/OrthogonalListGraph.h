#pragma once

#include "Graph.h"

extern const unsigned int MAX_VERTEX_NUM;


struct ArcBox {
    int tail;
    int head;
    ArcBox* phlinik;
    ArcBox* ptlink;
};

template<class T>
struct OLNode : public Vertex<T>
{
    OLNode() : Vertex<T>(), pfirstin(nullptr), pfirstout(nullptr) {}
    OLNode(const T& t) : Vertex<T>(t), pfirstin(nullptr), pfirstout(nullptr) {}
    OLNode(const Vertex<T>& v) : Vertex<T>(v), pfirstin(nullptr), pfirstout(nullptr) {}

    // T        Value ;  inherited from Vertex<T>
    ArcBox*     pfirstin;
    ArcBox*     pfirstout;
};

template<class T>
class OrthListGraph : public Graph<T>
{
public:
    OrthListGraph();
    virtual ~OrthListGraph();

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
    OLNode<T>	    m_vexs[MAX_VERTEX_NUM];
};

template<class T>
inline OrthListGraph<T>::OrthListGraph()
{
}

template<class T>
inline OrthListGraph<T>::~OrthListGraph()
{
}

template<class T>
inline const Vertex<T>* OrthListGraph<T>::GetVex(int i) const
{
    if (i<0 || i > m_vexnum)
        return nullptr;

    return &m_vexs[i];
}

template<class T>
inline const Vertex<T>* OrthListGraph<T>::FirstAdjVex(const Vertex<T>& vex) const
{
    const int i = LocateVex(vex);
    if (i != -1)
    {
        const ArcBox* pArc = m_vexs[i].pfirstout;
        if (pArc != nullptr)
            return &m_vexs[pArc->head];
    }

    return nullptr;
}

template<class T>
inline const Vertex<T>* OrthListGraph<T>::NextAdjVex(const Vertex<T>& vex, const Vertex<T>& vexAdj) const
{
    const int i = LocateVex(vex);
    const int j = LocateVex(vexAdj);

    if (i == -1 || j == -1)
        return nullptr;

    for (ArcBox* pout = m_vexs[i].pfirstout; pout != nullptr; pout = pout->ptlink)
    {
        if (j == pout->head)
        {
            return pout->ptlink ? &m_vexs[pout->ptlink->head] : nullptr;
        }
    }

    return nullptr;
}

template<class T>
inline void OrthListGraph<T>::InsertVex(const Vertex<T>& vex)
{
    m_vexs[m_vexnum++] = vex;
}

template<class T>
inline void OrthListGraph<T>::InsertArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo)
{
    const int i = LocateVex(vexFrom);
    const int j = LocateVex(vexTo);
    if (i != -1 && j != -1)
    {
        ArcBox** pptlink = &(m_vexs[i].pfirstout);
        while ((*pptlink) != nullptr)
        {
            if (j == (*pptlink)->head)
            {
                std::cout << "The arc from vertex " << i << "to vertex " << j << " is already existed!!!" << std::endl;
                return;
            }

            pptlink = &((*pptlink)->ptlink);
        }

        ArcBox** pphlink = &(m_vexs[j].pfirstin);
        while ((*pphlink) != nullptr)
        {
            if (i == (*pphlink)->tail)
                return;

            pphlink = &((*pphlink)->phlinik);
        }

        ArcBox* pArc = new ArcBox();
        pArc->tail = i; pArc->head = j;
        pArc->phlinik = nullptr;  pArc->ptlink = nullptr;

        (*pptlink) = pArc;
        (*pphlink) = pArc;

    }
}

template<class T>
inline void OrthListGraph<T>::DeleteVex(const Vertex<T>& vex)
{
    const int i = LocateVex(vex);
    if (i != -1)
    {
        // delete all the out arcs of the vertex
        ArcBox* pout = m_vexs[i].pfirstout;
        while (pout != nullptr)
        {
            ArcBox* ptlink = pout->ptlink;
            ArcBox* phlink = pout->phlinik;
            const int head = pout->head;

            // Bridge the in-links as the vertex will break
            for (ArcBox** ppin = &(m_vexs[head].pfirstin); (*ppin) != nullptr; ppin = &((*ppin)->phlinik))
            {
                if ((*ppin) == pout)
                {
                    *ppin = phlink;
                    break;
                }
            }

            // delete the arc/link
            delete pout;

            // move to next out/tail link
            pout = ptlink;
        }

        // delete all the in arcs of the vertex
        ArcBox* pin = m_vexs[i].pfirstin;
        while (pin != nullptr)
        {
            ArcBox* ptlink = pin->ptlink;
            ArcBox* phlink = pin->phlinik;
            const  int tail = pin->tail;

            for (ArcBox** ppout = &(m_vexs[tail].pfirstout); (*ppout) != nullptr; ppout = &((*ppout)->ptlink))
            {
                if ((*ppout) == pin)
                {
                    *ppout = ptlink;
                    break;
                }
            }

            // delete the link
            delete pin;

            // move to next in/head link
            pin = phlink;
        }

        // delete the vertex itself
        m_vexs[i].Value = "";
        m_vexs[i].pfirstin = nullptr;
        m_vexs[i].pfirstout = nullptr;

        m_vexnum--;
    }
}

template<class T>
inline void OrthListGraph<T>::DeleteArc(const Vertex<T>& vexFrom, const Vertex<T>& vexTo)
{
}
