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
	class Tile;

	//typedef std::vector<pkr::Vector2> Path;		//could also be vector<node*>
	typedef std::list<Node*> NodeList;
	typedef std::list<Tile*> TileList;

	struct Edge
	{
		Node*	target;
		float	cost;			//The traversal cost to move through this edge

	public:
		Edge() : target(nullptr), cost(0) {}		//Default
		Edge(Node* nodeTo) : target(nodeTo), cost(0) {}		//Overload (zero cost)
		Edge(Node* nodeTo, float cost) : target(nodeTo), cost(cost) {}		//Overload
	};

	struct Node
	{
		Node*				parent = nullptr;
		float				G = INFINITY;					//G score
		float				H = INFINITY;					//Heuristic score
		float				F = 0;							//Final score
		pkr::Vector2		pos;							//WORLD COORDINATES
		pkr::Vector2		cPos;							//CANVAS/ISO COORDINATES
		std::vector<Edge*>	connections;

	public:
		~Node() { for (auto c : connections) { delete c; } }
		Node() : pos(0, 0), parent(nullptr) {}								//Default
		Node(pkr::Vector2 pos) : pos(pos), parent(nullptr) {}				//Overload (nullptr parent)
		Node(pkr::Vector2 pos, Node* parent) : pos(pos), parent(parent) {}	//Overload (not sure if this would be needed)

		//Connect
		static void connect(Node *nodeFrom, Node *nodeTo, float cost = 1.0f) {		//Set connection (helper function?)
			Edge* edge = new Edge(nodeTo, cost);			//Create new edge and connect to TARGET node and set costs
			nodeFrom->connections.push_back(edge);			//Connect edge to RECEIVING node
		}

		//Compare function objects for use with std::list::sort()
		static bool compareGscore(Node *a, Node *b) { return a->G < b->G; }
		static bool compareFscore(Node *a, Node *b) { return a->F < b->F; }
	};

	struct Path : public std::vector<pkr::Vector2>
		//std::vector has no virtual destructor so don't call delete on the elements?
	{
		using	std::vector<pkr::Vector2>::vector;			//Use the constructor from std::vector

	public:
		size_t		index = 0;			//Important that this is init to 0!!!
		float		radius = 10.0f;		//Custom parameter

	public:
		bool		isAvailable() const { return !empty(); }
		
		pkr::Vector2 getWaypoint() { return this->at(index); }		//Get the current waypoint position

		void		next() { ++index; }
		
		void		reset()		//Clears and resets working index
		{
			index = 0;
			this->clear();
		}

		bool		endReached() const { return index > this->size()-1; }

		//Range checked overrides
		pkr::Vector2& operator[](size_t i) { return std::vector<pkr::Vector2>::at(i); }
		const pkr::Vector2& operator[](size_t i) const { return std::vector<pkr::Vector2>::at(i); }
	};


}