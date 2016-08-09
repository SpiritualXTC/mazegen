#pragma once
/********************************************************************
File: maze.h
Author: s3435406
Desc: Maze data structure
********************************************************************/
#include <cstdint>
#include <vector>

#include "maze_types.h"

namespace maze
{
/*
	Maze!
*/
class Maze
{
public:
	static const int DEFAULT_SIZE = 100;
	static const int MIN_SIZE = 2;

public:
	Maze(int32_t width, int32_t height);
	virtual ~Maze();


	bool addEdge(const MazeEdge & edge);
	bool addEdge(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

	int32_t width() const { return _width; }
	int32_t height() const { return _height; }

	const std::vector<MazeEdge> & edges() const { return _edges; }
	const std::vector<MazeNode> & nodes() const { return _nodes; }

	/*
		Get a const reference to the node @ (x, y)
	*/
	const inline MazeNode & getNode(int32_t x, int32_t y) const
	{
		return _nodes[convertToNodeIndex(x, y)];
	}

	


private:
	/*
		Convert the (x, y) coordinate into the Node index
	*/
	inline int32_t convertToNodeIndex(int32_t x, int32_t y) const
	{
		return y * _width + x;
	}



	bool addAdjacency(MazeNode & node, int32_t adjX, int32_t adjY);

	std::vector<MazeNode> _nodes;
	std::vector<MazeEdge> _edges;

	int32_t _width = 0;
	int32_t _height = 0;
};

}
