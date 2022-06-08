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
	if (IsEmpty())
	{
		m_pRoot->SetData(a_nValue);
	}
	else
	{
		TreeNode* current = m_pRoot;
		TreeNode* currentParent = nullptr;
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
			currentParent->SetLeft(current);
		}
		else
		{
			currentParent->SetRight(current);
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
		if(a_nSearchValue == pCurrent->GetData())
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
	TreeNode* toRemove = nullptr;
	TreeNode* removeParent = nullptr;
	FindNode(a_nValue, toRemove, removeParent);
	if (toRemove->GetRight() != nullptr)
	{
		TreeNode* rightMin = toRemove->GetRight()->GetLeft();
		TreeNode* rightMinParent = toRemove->GetRight();
		while (rightMin != nullptr)
		{
			rightMinParent = rightMin;
			rightMin = rightMin->GetLeft();
			
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