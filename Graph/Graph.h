#pragma once
#include <iostream>

template <class T>
struct Vertex
{ 
    Vertex() {}
    Vertex(const T& v) : Value(v) {}
	T			Value;
};

template<class T>
class Vistor
{
public:
	bool operator()(const Vertex<T>& vex);
};

template<class T>
inline bool Vistor<T>::operator()(const Vertex<T>& vex)
{
	std::cout << "Visiting vertx: " << vex.Value << std::endl;
	return true;
}

template<class T>
class Graph
{
public:
	Graph() = default;
	virtual ~Graph() = default;

	// Get the position of the vertex, -1 not exist.
	virtual int LocateVex(const Vertex<T>& vex) const = 0;

	// Get vertex value
	virtual T GetVex(const Vertex<T>& vex) const = 0;

	// Set vertex value
	virtual void PutVex(const Vertex<T>& vex, const T& val) = 0;

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
	virtual void DFSTraverse(const Vertex<T>& vex,  Vistor<T> visit) = 0;

	// Breadth-First Search traverse the graph, start from vex and call Visitor once for each vertex
	virtual void BFSTraverse(const Vertex<T>& vex, Vistor<T> visit) = 0;

};

