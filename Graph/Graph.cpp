// Graph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "AdjMatrixGraph.h"
#include "AdjListGraph.h"
#include "OrthogonalListGraph.h"


/*
7.1 G1:
V1----------->V2
|/ \
|	   \
\|/	 \
V3---->V4
*/
using StringVex = Vertex<std::string>;

int main()
{
	std::unique_ptr<Graph<std::string>> graph {new AdjMatrixDiGraph<std::string>()};
   //std::unique_ptr<Graph<std::string>> graph{ new AdjListGraph<std::string>() };
  //std::unique_ptr<Graph<std::string>> graph{ new OrthListGraph<std::string>() };


	// Insert vextex
    StringVex v1{ "V1" }, v2{ "V2" }, v3{ "V3" }, v4{ "V4" };
	graph->InsertVex(std::move(v1));
	graph->InsertVex(std::move(v2));
	graph->InsertVex(std::move(v3));
	graph->InsertVex(std::move(v4));

	StringVex vexFrom, vexTo;

	// Add Arcs
	// V1->V2
	vexFrom.Value = "V1"; vexTo.Value = "V2";
	graph->InsertArc(vexFrom, vexTo);
	//V1->V3
	vexFrom.Value = "V1"; vexTo.Value = "V3";
	graph->InsertArc(vexFrom, vexTo);
	//V3->V1
	vexFrom.Value = "V3"; vexTo.Value = "V1";
	graph->InsertArc(vexFrom, vexTo);
    //V3->V4
    vexFrom.Value = "V3"; vexTo.Value = "V4";
    graph->InsertArc(vexFrom, vexTo);
	//V4->V1
	vexFrom.Value = "V4"; vexTo.Value = "V1";
	graph->InsertArc(vexFrom, vexTo);
    //V4->V2
    vexFrom.Value = "V4"; vexTo.Value = "V2";
    graph->InsertArc(vexFrom, vexTo);
    //V4->V3
    vexFrom.Value = "V4"; vexTo.Value = "V3";
    graph->InsertArc(vexFrom, vexTo);

    // Print all the arcs starting from V4
    StringVex vex; vex.Value = "V4";
    std::cout << "Print all the adjacent vertexs from " << vex.Value << std::endl;
    for (auto pAdjVex = graph->FirstAdjVex(vex); pAdjVex != nullptr; pAdjVex = graph->NextAdjVex(vex, *pAdjVex))
    {
        std::cout << (pAdjVex ? pAdjVex->Value : "null") << std::endl;
    }

    // Depth-First Traverse 
    vex.Value = "V3";
    std::cout << "Depth-First traverse from " << vex.Value << std::endl;
    graph->DFSTraverse(vex, Visitor<std::string>());

    // Breadth-First Traverse
    std::cout << "Breadth-First traverse from " << vex.Value << std::endl;
    graph->BFSTraverse(vex, Visitor<std::string>());


	// Delete the vex
    vex.Value = "V1";
    std::cout << "Delete the vertex " << vex.Value << std::endl;
	graph->DeleteVex(vex);

	vex.Value = "V3";
	std::cout << vex.Value<<"'s adjacent vertexs: " << std::endl;
	for (auto pAdjVex = graph->FirstAdjVex(vex); pAdjVex != nullptr; pAdjVex=graph->NextAdjVex(vex, *pAdjVex))
	{
		std::cout << (pAdjVex ? pAdjVex->Value : "null") << std::endl; 
	}

	system("pause");
   return 0;
}


