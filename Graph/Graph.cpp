// Graph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "AdjMatrixGraph.h"

#include <memory>

using StringVex = Vertex<std::string>;

int main()
{

	/*
	7.1 G1:
	V1----------->V2
	|/ \
	|	   \
	\|/	 \
	V3---->V4
	*/

	std::unique_ptr<Graph<std::string>> graph {new AdjMatrixDiGraph<std::string>()};

	// Insert vextex
	StringVex v1{ "V1" }, v2{ "V2" }, v3{ "V3" }, v4{ "V4" };
	graph->InsertVex(std::move(v1));
	graph->InsertVex(std::move(v2));
	graph->InsertVex(std::move(v3));
	graph->InsertVex(std::move(v4));

	/* 
	Adjcent matrix :
				V1	V2	V3	V4
		------------------------ -
		V1 | 0     1      1     0
		V2 | 0	  0	  0	  0
		V3 | 0     0      0     1
		V4 | 1     0      0     0
		--------------------------
	*/
	StringVex vexFrom, vexTo;

	// Add Arcs
	// V1->V2
	vexFrom.Value = "V1"; vexTo.Value = "V2";
	graph->InsertArc(vexFrom, vexTo);
	//V1->V3
	vexFrom.Value = "V1"; vexTo.Value = "V3";
	graph->InsertArc(vexFrom, vexTo);
	//V3->V4
	vexFrom.Value = "V3"; vexTo.Value = "V4";
	graph->InsertArc(vexFrom, vexTo);
	//V4->V1
	vexFrom.Value = "V4"; vexTo.Value = "V1";
	graph->InsertArc(vexFrom, vexTo);
	
	StringVex vex; vex.Value = "V2";
	// Delete the vex
	graph->DeleteVex(vex);

	vex.Value = "V1";
	std::cout << vex.Value<<"'s adjacent vertexs: " << std::endl;
	for (auto pAdjVex = graph->FirstAdjVex(vex); pAdjVex != nullptr; pAdjVex=graph->NextAdjVex(vex, *pAdjVex))
	{
		std::cout << (pAdjVex ? pAdjVex->Value : "null") << std::endl;
	}

	system("pause");
    return 0;
}


