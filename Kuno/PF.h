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
		pkr::Vector2		pos;							//WORLD COORDINATES
		pkr::Vector2		cPos;						//CANVAS/ISO COORDINATES
		std::vector<Edge*>	connections;

		~Node() { for (auto c : connections) { delete c; } }
		Node() : G(INFINITY), pos(0, 0), parent(nullptr) {}								//Default
		Node(pkr::Vector2 pos) : G(INFINITY), pos(pos), parent(nullptr) {}					//Overload (nullptr parent)
		Node(pkr::Vector2 pos, Node* parent) : G(INFINITY), pos(pos), parent(parent) {}	//Overload (not sure if this would be needed)

		//Connect
		static void connect(Node *nodeFrom, Node *nodeTo, float cost = 1.0f) {		//Set connection (helper function?)
			Edge* edge = new Edge(nodeTo, cost);			//Create new edge and connect to TARGET node and set costs
			nodeFrom->connections.push_back(edge);			//Connect edge to RECEIVING node
		}

		//Compare function objects for use with std::list::sort()
		static bool compareGscore(Node *a, Node *b) { return a->G < b->G; }
		static bool compareFscore(Node *a, Node *b) { return a->F() < b->F(); }
	};

}