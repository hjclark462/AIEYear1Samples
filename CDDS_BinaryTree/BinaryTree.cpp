/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while (m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	TreeNode* newNode = new TreeNode(a_nValue);
	if (IsEmpty())
	{
		
		m_pRoot = newNode;
	}
	else
	{
		TreeNode* current = m_pRoot;
		TreeNode* currentParent = nullptr;
		if (!Find(a_nValue))
		{
			while (current != nullptr)
			{
				currentParent = current;
				if (a_nValue < current->GetData())
				{
					current = current->GetLeft();
				}
				else
				{
					current = current->GetRight();
				}
			}
			if (a_nValue < currentParent->GetData())
			{
				currentParent->SetLeft(newNode);
			}
			else
			{
				currentParent->SetRight(newNode);
			}
		}
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	TreeNode* pCurrent = m_pRoot;
	TreeNode* pParent = nullptr;
	while (pCurrent != nullptr)
	{
		if (a_nSearchValue == pCurrent->GetData())
		{
			return true;
			ppOutNode = pCurrent;
			ppOutParent = pParent;
		}
		else
		{
			pParent = pCurrent;
			if (a_nSearchValue < pCurrent->GetData())
			{
				pCurrent = pCurrent->GetLeft();
			}
			else
			{
				pCurrent = pCurrent->GetRight();
			}
		}
	}
	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	TreeNode* root = m_pRoot;
	TreeNode* foundNode;
	TreeNode* foundParent;
	FindNode(a_nValue, foundNode, foundParent);
	//Removing the Node starts here
	TreeNode* leftOfRemoved = foundNode->GetLeft();
	TreeNode* rightOfRemoved = foundNode->GetRight();
	if (rightOfRemoved != nullptr)
	{
		TreeNode* replacementNode = rightOfRemoved;
		TreeNode* replacementPrevious = foundNode;
		while (replacementNode->GetLeft() != nullptr)
		{
			replacementPrevious = replacementNode;
			replacementNode = replacementNode->GetLeft();
		}
		TreeNode* rightOfReplacement = replacementNode->GetRight();
		
		if (foundParent != nullptr)
		{
			if (foundParent->GetLeft() == foundNode)
			{
				foundParent->SetLeft(replacementNode);
			}
			else
			{
				foundParent->SetRight(replacementNode);
			}
		}
		else if (rightOfReplacement != nullptr && replacementPrevious != foundNode)
		{
			replacementPrevious->SetLeft(rightOfReplacement);
		}
		else
		{
			root = replacementNode;
		}
		replacementNode->SetLeft(leftOfRemoved);
		if (rightOfRemoved != replacementNode)
		{
			replacementNode->SetRight(rightOfRemoved);
		}
		delete foundNode;
	}
	else if (leftOfRemoved != nullptr)
	{
		if (foundParent != nullptr)
		{
			if (foundParent->GetLeft() == foundNode)
			{
				foundParent->SetLeft(leftOfRemoved);
			}
			else
			{
				foundParent->SetRight(leftOfRemoved);
			}
			delete foundNode;
		}
		else
		{
			root = leftOfRemoved;
		}
	}
	else
	{
		if (foundParent != nullptr)
		{
			if (foundParent->GetLeft() == foundNode)
			{
				foundParent->SetLeft(nullptr);
			}
			else
			{
				foundParent->SetRight(nullptr);
			}
			delete foundNode;
		}
	}
}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);

			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}