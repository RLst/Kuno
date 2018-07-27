#pragma once

#include <pkr\Vector2.h>
#include <vector>
#include <list>
#include <Renderer2D.h>

//Pathfinding related methods and implementations
namespace pf {

	struct Node;

	struct Edge
	{
		Node*	connectTo;
		float	cost;			//The traversal cost to move through this edge

		Edge() : connectTo(nullptr), cost(0) {}		//Default

		Edge(Node* nodeTo) : connectTo(nodeTo), cost(0) {}		//Overload (zero cost)

		Edge(Node* nodeTo, float cost) : connectTo(nodeTo), cost(cost) {}		//Overload
	};

	struct Node
	{
		Node*				parent;
		float				gScore;
		float				hScore;
		float				fScore() const { return gScore + hScore; }
		pkr::Vector2		pos_tmp;				//Might put this in Tile instead
		std::vector<Edge*>	connections;

		Node() : gScore(0), /*pos(0, 0),*/ parent(nullptr) {}		//Default

		Node(pkr::Vector2 pos) : gScore(0), /*pos(pos),*/ parent(nullptr) {}		//Overload (nullptr parent)

		Node(pkr::Vector2 pos, Node* parent) : gScore(0), /*pos(pos),*/ parent(parent) {}		//Overload

		//Set connection (helper function?)
		void static connect(Node *nodeFrom, Node *nodeTo, float cost) {
			//Create new edge and connect to TARGET node and set costs
			Edge* edge = new Edge(nodeTo, cost);
			//Connect edge to RECEIVING node
			nodeFrom->connections.push_back(edge);
		}
	};

	typedef std::list<Node*> NodeList;

	class Graph
	{
	protected:
		NodeList	m_nodes;		//***The graph's container of nodes; should I use list or vectors?

	public:
		Graph() {};
		~Graph() {			//Delete all nodes
			for (auto &node : m_nodes) {
				delete node;
				node = nullptr;
			}
		}

		//Accessors
		NodeList& getNodes() { return m_nodes; }

		Node*	addNode(pkr::Vector2 pos);

		//Remove the given node
		void	removeNode(Node* node) { m_nodes.remove(node); }
		void	addConnection(Node* nodeFrom, Node* nodeTo, float cost = 1.0f);
		Node*	findNode(pkr::Vector2 position, float searchRadius = 0.0f);			//Return node that is at position or within range
		NodeList& findNodes(pkr::Vector2 position, float searchRadius = 0.0f);	//Return a list of nodes that are within a certain search radius

		NodeList	AStarSearch(Node* startNode, Node* endNode);		//Returns A* path
		NodeList	DjikstraSearch(Node* startNode, Node* endNode);		//Returns djikstra path

		//Cores
		void	draw(aie::Renderer2D* renderer);
		//void	findNodes(std::list<Node*> &list, pkr::Vector2 position, float distance);	//do I need this?
	};
}

