#include "CStringList.h"

using namespace std;

CStringList::CStringList()
{
	m_firstNode = make_unique<Node>("", nullptr, nullptr);
}

void CStringList::PushFront(const std::string& data)
{
	auto newNode = make_unique<Node>(data, nullptr, nullptr);
	newNode->next = nullptr;

	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else // empty list
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

//size_t m_size = 0;
//std::unique_ptr<Node> m_firstNode;
//Node* m_lastNode = nullptr;