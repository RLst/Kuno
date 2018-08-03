//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#include "PF.h"

namespace pf {

	bool Graph::sortAscendingGscore(Node * a, Node * b)
	{
		return a->G < b->G;
	}

	bool Graph::sortAscendingFscore(Node *a, Node *b)
	{
		return a->F() < b->F();
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

	//Path Graph::getDjikstraPath(Node * startNode, Node * endNode) const
	//{
	//	/*
	//	//Inits
	//	Node*	currentNode = nullptr;

	//	NodeList	openList;	//Let openList be a list of nodes
	//	NodeList	closedList;	//Let closedList be a list of nodes

	//	startNode->parent = nullptr;	//Set startnode to null
	//	openList.push_back(startNode);	//Add startnode to openList

	//	while (!openList.empty()) {

	//		openList.sort(sortAscendingGscore);		//Sort openList by node's.gscore //(startNode, endNode)

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

	//	*/

	//	//Calculate path, in this example as positions
	//	//typedef std::stack<pkr::Vector2> Path;
	//	Path path;
	//	//currentNode = endNode;
	//	//while (currentNode != nullptr) {
	//	//	path.push_back(currentNode->cPos);
	//	//	currentNode = currentNode->parent;
	//	//}
	//	return path;
	//}

	//Path Graph::getAStarPath(Node * startNode, Node * endNode) const
	//{
	//	//Inits
	//	Node* currentNode;
	//	//int currentStep = 0;
	//	NodeList	openList;
	//	NodeList	closedList;

	//	//Set all parents to null and G scores to infinity
	//	for (auto node : m_nodes) {
	//		node->parent = nullptr;
	//		node->G = INFINITY;
	//		//node->F = INFINITY;
	//	}
	//	
	//	//Clear and push start node onto open list
	//	startNode->parent = nullptr;		//This will act as the root; will be used when tracing back
	//	startNode->G = 0;				//0 because there's no traversal yet
	//	openList.push_back(startNode);

	//	//Slight optimization; Stop once you get to the node you're looking for
	//	//Downside: Might not always find the shortest parth
	//	//for (auto it = openList.begin(); it != openList.end(); it++) {
	//	//	if (currentNode == *it) {
	//	//		endNode = node;
	//	//		break;
	//	//	}
	//	//}

	//	//While queue is not empty
	//	while (!openList.empty())
	//	{
	//		//Sort open list based on the F score
	//		openList.sort(pf::Node::compareFscore);		//Sort takes in a function object

	//		currentNode = openList.front();				//Get current work node of the end of the queue
	//		openList.pop_front();						//Remove node from the queue
	//		closedList.push_back(currentNode);			//Current node is now traversed (mark it as traversed)

	//		if (currentNode == endNode) break;			//Goal node found so break out

	//		for (auto c : currentNode->connections) {		//[Loop through it's edges]

	//			//Add c.target to openList if not in closedList
	//			for (auto traversed : closedList) {
	//				if (c->target == traversed) {
	//					openList.push_back(c->target);
	//				}
	//			}

	//			//c.target.gScore = currentNode.gScore + c.cost
	//			c->target->G = currentNode->G + c->cost;

	//			//// A* modifications ////
	//			c->target->H = pkr::Vector2::distance(c->target->cPos, endNode->cPos);			//n.hscore = distance from n to endnode
	//			//c->target->F();		//Might not be required as F() automatically sums G + H	//n.fscore = n.gscore + h.hscore
	//			//////////////////////////

	//			c->target->parent = currentNode;				//c.target.parent = currentNode
	//		}
	//	}

	//	Path AstarSolution;
	//	auto workNode = endNode;
	//	while (workNode != nullptr) {
	//		AstarSolution.push_back(workNode->cPos);
	//		workNode = workNode->parent;
	//	}
	//	return AstarSolution;
	//}

	void Graph::drawGraph(aie::Renderer2D * renderer)
	{
		for (auto node : m_nodes) {

			//Draw nodes on top
			renderer->setRenderColour(1, 0.3f, 0);
			renderer->drawCircle(node->cPos.x, node->cPos.y, 0.1f);
			//renderer->drawBox(node->pos.x, node->pos.y, 10, 10);

			//Draw edges below nodes 
			for (auto c : node->connections)
			{
				renderer->setRenderColour(0.9f, 0.9f, 0.9f);
				renderer->drawLine(node->cPos.x, node->cPos.y, c->target->cPos.x, c->target->cPos.y, 2.0f, 0.2f);
			}
		}
	}

}
