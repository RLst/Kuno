#include "PF.h"

namespace PF {

PF::Node * PF::Graph::addNode(pkr::Vector2 pos)
{
	//Create new node with set properties, push it onto graph node list and return
	Node* newNode = new Node(pos);
	m_nodes.push_back(newNode);
	return newNode;
}

void PF::Graph::addConnection(Node * nodeFrom, Node * nodeTo, float cost)
{
	Node::connect(nodeFrom, nodeTo, cost);
	//Edge* edge = new Edge(nodeTo, cost);			//Create new edge and connect to TARGET node and set costs
	//nodeFrom->connections.push_back(edge);			//Connect edge to RECEIVING node
}

Node * Graph::findNode(pkr::Vector2 position, float searchRadius)
{
	for (auto node : m_nodes) {
		//Return node that is within range of search position
		if (pkr::Vector2::distance(node->pos, position) < searchRadius)
			return node;
	}
}

void PF::Graph::draw(aie::Renderer2D * renderer)
{
	for (auto node : m_nodes) {
		//Draw the edges first (below)
		for (auto it : node->connections)
		{
			Edge* edge = it;
			renderer->setRenderColour(1, 1, 1);
			renderer->drawLine(node->pos.x, node->pos.y, edge->connectTo->pos.x, edge->connectTo->pos.y);
		}

		//Draw the nodes after (top)
		renderer->setRenderColour(1, 0.3, 0);		//Required?
		//renderer->drawBox(node->pos.x, node->pos.y, 10, 10);
		renderer->drawCircle(node->pos.x, node->pos.y, 5);
	}
}

}
