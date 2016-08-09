/********************************************************************
File: graph.h
Author: s3435406
Desc: Custom "Set" to work with prims algorithm
********************************************************************/
#pragma once

#include <vector>
#include <unordered_map>

namespace generators
{
	/*
		Custom Set to work with Prims Algorithms
	*/
	template <typename NODE, typename T>
	class PrimSet
	{
	private:
		struct Node
		{
			bool connected;
			NODE node;
		};

	public:
		PrimSet() {}
		virtual ~PrimSet() {}

		/*
			Adds a Data Node
		*/
		void addNode(const NODE & node)
		{
			// Add the Node
			_nodes.push_back({ false, node });
		}


		/*
			Gets the Data Node
		*/
		NODE & getNode(int32_t index)
		{
			return _nodes.at(index).node;
		}


		/*
			Is the Node Connected ?
		*/
		inline bool isConnected(int32_t index)
		{
			return _nodes.at(index).connected;
		}

		/*
			Mark this node as connected!
		*/
		inline void connect(int32_t index)
		{
			_nodes.at(index).connected = true;
		}



		/*
			Pop and Delete a node from the list
		*/
		T pop()
		{
			// Select Node
			int32_t index = rand() % _open.size();
			T t = _open[index];

			// Delete Node
			_open[index] = *(_open.end() - 1);
			_open.erase(_open.end() - 1);

			return t;
		}

		/*
			Push a node to the open list
		*/
		void push(const T & t)
		{
			_open.push_back(t);
		}


		/*
			Is the open list empty?
		*/
		inline bool empty()
		{
			return _open.empty();
		}


	private:
		std::vector<T> _open;

		std::vector<Node> _nodes;
	};

}