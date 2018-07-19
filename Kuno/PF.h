#pragma once

#include <pkr\Vector2.h>
#include <vector>
#include <list>
#include <Renderer2D.h>

//Pathfinding related methods and implementations
namespace PF {

	struct Node;

	struct Edge
	{
		Node*	connectTo;
		float	cost;

		Edge() : connectTo(nullptr), cost(0) {}		//Default

		Edge(Node* nodeTo) : connectTo(nodeTo), cost(0) {}		//Overload (zero cost)

		Edge(Node* nodeTo, float cost) : connectTo(nodeTo), cost(cost) {}		//Overload
	};

	struct Node
	{
		Node*				parent;
		float				gScore;
		pkr::Vector2		pos;
		std::vector<Edge*>	connections;

		Node() : gScore(0), pos(0, 0), parent(nullptr) {}		//Default

		Node(pkr::Vector2 pos) : gScore(0), pos(pos), parent(nullptr) {}		//Overload (nullptr parent)

		Node(pkr::Vector2 pos, Node* parent) : gScore(0), pos(pos), parent(parent) {}		//Overload

																							//Set connection (helper function?)
		void static connect(Node *nodeFrom, Node *nodeTo, float cost) {
			//Create new edge and connect to TARGET node and set costs
			Edge* edge = new Edge(nodeTo, cost);
			//Connect edge to RECEIVING node
			nodeFrom->connections.push_back(edge);
		}
	};

	class Graph
	{
	protected:
		std::list<Node*>	m_nodes;		//The graph's container of nodes; should I use list or vectors?
		aie::Texture*		m_texture;

	public:
		Graph() {};
		~Graph() {			//Delete all nodes
			for (auto &node : m_nodes) {
				delete node;
				node = nullptr;
			}
		}

		Node*	addNode(pkr::Vector2 pos);

		//Remove the given node
		void	removeNode(Node* node) { m_nodes.remove(node); }

		void	addConnection(Node* nodeFrom, Node* nodeTo, float cost = 1.0f);

		void	draw(aie::Renderer2D* renderer);

		std::list<Node*>	AStarSearch(Node* startNode, Node* endNode);		//Returns A* path

		std::list<Node*>	DjikstraSearch(Node* startNode, Node* endNode);		//Returns djikstra path

		void	findNodes(std::list<Node*> &list, pkr::Vector2 position, float distance);	//do I need this?
		void	update(float deltaTime);		//Don't think this is needed
		//void	findPathDijkstra(Node* nodeStart, const std::list<Node*> &endNodes, std::list<Node*> &outPath);
	};
}

