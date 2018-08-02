//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#include "PF.h"

//#include <list>
//#include <stack>

namespace pf {

	bool Graph::sortAscending(Node * a, Node * b) const
	{
		return a->gScore < b->gScore;
	}

	Graph::~Graph()
	{			//Delete all nodes
		for (auto &node : m_nodes) 
		{
			delete node;
			node = nullptr;
		}
	}

	pf::Node * pf::Graph::addNode(pkr::Vector2 pos)
	{
		//Create new node with set properties, push it onto graph node list and return
		Node* newNode = new Node(pos);
		m_nodes.push_back(newNode);
		return newNode;
	}

	void pf::Graph::addConnection(Node * nodeFrom, Node * nodeTo, float cost)
	{
		Node::connect(nodeFrom, nodeTo, cost);
		//Edge* edge = new Edge(nodeTo, cost);			//Create new edge and connect to TARGET node and set costs
		//nodeFrom->connections.push_back(edge);			//Connect edge to RECEIVING node
	}

	Node * Graph::findNode(pkr::Vector2 position, float searchRadius)
	{
		for (auto node : m_nodes) {
			//Return node that is within range of search position
			if (pkr::Vector2::distance(node->cPos, position) < searchRadius)
				return node;
		}
	}

	std::list<Node*>& Graph::findNodes(pkr::Vector2 position, float searchRadius)
	{
		NodeList foundNodes;
		for (auto node : m_nodes) {
			//Push within range nodes onto list
			if (pkr::Vector2::distance(node->cPos, position) < searchRadius)
				foundNodes.push_back(node);
		}
		return foundNodes;
	}

	Path Graph::getDjikstraPath(Node * startNode, Node * endNode) const
	{
	//	//Inits
	//	Node*	currentNode = nullptr;

	//	NodeList	openList;	//Let openList be a list of nodes
	//	NodeList	closedList;	//Let closedList be a list of nodes

	//	startNode->parent = nullptr;	//Set startnode to null
	//	openList.push_back(startNode);	//Add startnode to openList

	//	while (!openList.empty()) {

	//		openList.sort(sortAscending(startNode, endNode));		//Sort openList by node's.gscore //(startNode, endNode)

	//		//Remove current node from openlist
	//		currentNode = openList.front();	
	//		openList.pop_front();		

	//		//End path found, break out of loop
	//		if (currentNode == endNode)
	//			break;

	//		//Add currentNode to closedList (marking it as traversed)
	//		closedList.push_back(currentNode);

	//		//For all connection c in current node
	//		for (auto edge : currentNode->connections) {
	//			//Add c.target to openList if not in closedList
	//			for (auto d : closedList) {
	//				if (d == edge->target) {
	//					//In closedList, do nothing?
	//				}
	//				else {
	//					//Not in closedList so add to openList ?
	//					openList.push_back(edge->target);
	//				}
	//			}
	//			edge->target->gScore = currentNode->gScore + edge->cost;
	//			edge->target->parent = currentNode;
	//		}
	//	}

		//Calculate path, in this example as positions
		//typedef std::stack<pkr::Vector2> Path;
		Path path;
		//auto currentNode = endNode;
		//while (currentNode != nullptr) {
		//	path.push(currentNode->pos_tmp);
		//	currentNode = currentNode->parent;
		//}
		return path;
	}

	Path Graph::getAStarPath(Node * startNode, Node * endNode) const
	{
		////Set all parents nodes to

		////Set all nodes to null..
		////Set all gScores to infinity...

		//int currentStep = 0;
		//std::list<Node*> openList;				//Priority queue
		//std::list<Node*> closedList;			//Traversed queue

		////Set initial end node
		//Node* endNode = nullptr;

		////Set G score and parent
		//startNode->gScore = 0;
		//startNode->parent = nullptr;

		////Push start node onto priority queue
		//openList.push_back(startNode);

		////While queue (priority) not empty
		//while (!openList.empty()) {

		//	//Get the current node off the end of the queue and remove it
		//	//openList.
		//}

		return Path();
	}

	void Graph::draw(aie::Renderer2D * renderer)
	{
		//Draw edges on the bottom
		for (auto node : m_nodes) {
			for (auto it : node->connections)
			{
				Edge* edge = it;
				renderer->setRenderColour(1, 1, 1);
				renderer->drawLine(node->cPos.x, node->cPos.y, edge->target->cPos.x, edge->target->cPos.y, 2.0f, 0.2f);
			}
		}

		//Draw nodes on top
		for (auto node : m_nodes) {
			renderer->setRenderColour(1, 0.3f, 0);		//Required?
			//renderer->drawBox(node->pos.x, node->pos.y, 10, 10);
			renderer->drawCircle(node->cPos.x, node->cPos.y, 0.1f);
		}
	}

}
