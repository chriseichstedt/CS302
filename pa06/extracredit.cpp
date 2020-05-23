//////////////////////////////////////////////////////////////////////////
//programming exercise #3 (extra credit)
//////////////////////////////////////////////////////////////////////////
template <typename DataType>
bool ExprTree<DataType> :: isEquivalent(const ExprTree& source) const
{
	return isEquivalent_Helper(root, source.root);
}

template <typename DataType>
bool ExprTree<DataType> :: isEquivalent_Helper(ExprTreeNode *end, ExprTreeNode *start) const
{
	if(end == NULL && start == NULL)
	{
		return true;
	}
	
	else if(end != NULL && start != NULL)
	{
		if(end->dataItem == start->dataItem)
		{
			if(isEquivalent_Helper(end->left, start->left) && isEquivalent_Helper(end->right, start->right))
			{
				return true;
			}
			
			else if(isEquivalent_Helper(end->left, start->right) && isEquivalent_Helper(end->right, start->left))
			{
				if(end->dataItem == '+' || end->dataItem == '*')
				{
					return true;
				}
				
				else
				{
					return false;
				}
			}
		
			else
			{
				return false;
			}
		}
	}

	return false;
}
