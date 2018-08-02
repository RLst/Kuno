//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once

#include <pkr\Vector2.h>
#include <Renderer2D.h>
#include <vector>
#include <list>
#include <stack>

//Pathfinding related methods and implementations
namespace pf {

	struct Node;

	struct Edge
	{
		Node*	target;
		float	cost;			//The traversal cost to move through this edge

		Edge() : target(nullptr), cost(0) {}		//Default

		Edge(Node* nodeTo) : target(nodeTo), cost(0) {}		//Overload (zero cost)

		Edge(Node* nodeTo, float cost) : target(nodeTo), cost(cost) {}		//Overload
	};

	struct Node
	{
		Node*				parent;
		float				gScore;
		float				hScore;
		float				fScore() const { return gScore + hScore; }
		pkr::Vector2		cPos;				//CARTESIAN WORLD COORDINATES
		pkr::Vector2		iPos;				//ISOMETROC WORLD COORDINATES
		std::vector<Edge*>	connections;

		~Node() { for (auto c : connections) { delete c; } }
		Node() : gScore(0), cPos(0, 0), parent(nullptr) {}									//Default
		Node(pkr::Vector2 pos) : gScore(0), cPos(pos), parent(nullptr) {}					//Overload (nullptr parent)
		Node(pkr::Vector2 pos, Node* parent) : gScore(0), cPos(pos), parent(parent) {}		//Overload

		void static connect(Node *nodeFrom, Node *nodeTo, float cost = 1.0f) {		//Set connection (helper function?)
			Edge* edge = new Edge(nodeTo, cost);			//Create new edge and connect to TARGET node and set costs
			nodeFrom->connections.push_back(edge);			//Connect edge to RECEIVING node
		}
	};

	typedef std::vector<pkr::Vector2> Path;
	typedef std::list<Node*> NodeList;

	class Graph
	{
	private:
		bool	sortAscending(Node* a, Node* b) const;		//Helper function for priority queue sorting

	protected:
		NodeList	m_nodes;		//***The graph's container of nodes; should I use list or vectors?

	public:
		Graph() {};
		~Graph();

		//Accessors
		NodeList&	getNodes() { return m_nodes; }

		Node*		addNode(pkr::Vector2 pos);

		//Remove the given node
		void		removeNode(Node* node) { m_nodes.remove(node); }
		void		addConnection(Node* nodeFrom, Node* nodeTo, float cost = 1.0f);
		Node*		findNode(pkr::Vector2 position, float searchRadius = 0.0f);			//Return node that is at position or within range
		NodeList&	findNodes(pkr::Vector2 position, float searchRadius = 0.0f);		//Return a list of nodes that are within a certain search radius

		Path		getDjikstraPath(Node* startNode, Node* endNode) const;	
		Path		getAStarPath(Node* startNode, Node* endNode) const;

		//Cores
		void	draw(aie::Renderer2D* renderer);

	};
}