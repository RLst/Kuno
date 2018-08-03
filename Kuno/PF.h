//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once

#include <pkr\Vector2.h>
#include <Renderer2D.h>
#include <vector>
#include <list>

//Pathfinding related methods and implementations
namespace pf {

	struct Node;
	struct Tile;

	typedef std::vector<pkr::Vector2> Path;		//could also be vector<node*>
	typedef std::list<Node*> NodeList;
	typedef std::list<Tile*> TileList;

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
		Node*				parent = nullptr;
		float				G = INFINITY;					//G score should default to infinity?
		float				H;								//Heuristic score
		float				F() const { return G + H; }		//Final score
		pkr::Vector2		cPos;							//CARTESIAN WORLD COORDINATES
		pkr::Vector2		iPos;							//ISOMETRIC WORLD COORDINATES
		std::vector<Edge*>	connections;

		~Node() { for (auto c : connections) { delete c; } }
		Node() : G(INFINITY), cPos(0, 0), parent(nullptr) {}								//Default
		Node(pkr::Vector2 pos) : G(INFINITY), cPos(pos), parent(nullptr) {}					//Overload (nullptr parent)
		Node(pkr::Vector2 pos, Node* parent) : G(INFINITY), cPos(pos), parent(parent) {}	//Overload (not sure if this would be needed)

		//Connect
		static void connect(Node *nodeFrom, Node *nodeTo, float cost = 1.0f) {		//Set connection (helper function?)
			Edge* edge = new Edge(nodeTo, cost);			//Create new edge and connect to TARGET node and set costs
			nodeFrom->connections.push_back(edge);			//Connect edge to RECEIVING node
		}

		//Compare function objects for use with std::list::sort()
		static bool compareGscore(Node *a, Node *b) { return a->F() < b->F(); }
		static bool compareFscore(Node *a, Node *b) { return a->F() < b->F(); }
	};

	class Graph
	{
	private:
		//Compare function objects for use with std::list::sort()
		static bool	sortAscendingGscore(Node* a, Node* b);		//Helper function for priority queue sorting
		static bool	sortAscendingFscore(Node *a, Node *b);

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

		//Path		getDjikstraPath(Node* startNode, Node* endNode) const;	
		//Path		getAStarPath(Node* startNode, Node* endNode) const;

		//Cores
		void		drawGraph(aie::Renderer2D* renderer);		//Draws the basic

	};
}