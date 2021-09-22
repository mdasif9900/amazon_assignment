 
#include <stdio.h>



struct Node
{
	struct Node *left, *right;
	int key;
};


Node* newNode(int key)
{
	Node *temp = new Node;
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}


int findLevel(Node *root, int k, int level)
{
	// Base Case
	if (root == NULL)
		return -1;

	
	if (root->key == k)
		return level;

	int l = findLevel(root->left, k, level+1);
	return (l != -1)? l : findLevel(root->right, k, level+1);
}


Node *findDistUtil(Node* root, int n1, int n2, int &d1,
							int &d2, int &dist, int lvl)
{
	// Base case
	if (root == NULL) return NULL;

	
	if (root->key == n1)
	{
		d1 = lvl;
		return root;
	}
	if (root->key == n2)
	{
		d2 = lvl;
		return root;
	}

	
	Node *left_lca = findDistUtil(root->left, n1, n2,
								d1, d2, dist, lvl+1);
	Node *right_lca = findDistUtil(root->right, n1, n2,
								d1, d2, dist, lvl+1);

	
	if (left_lca && right_lca)
	{
		dist = d1 + d2 - 2*lvl;
		return root;
	}

	return (left_lca != NULL)? left_lca: right_lca;
}
int findDistance(Node *root, int n1, int n2)
{
	
	int d1 = -1, d2 = -1, dist;
	Node *lca = findDistUtil(root, n1, n2, d1, d2,dist, 1);

	if (d1 != -1 && d2 != -1)
		return dist;


	if (d1 != -1)
	{
		dist = findLevel(lca, n2, 0);
		return dist;
	}

	
	if (d2 != -1)
	{
		dist = findLevel(lca, n1, 0);
		return dist;
	}

	return -1;
}


int main()
{
    int n1,n2;

	Node * root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);
	root->right->left->right = newNode(8);
// 	printf("Enter two nodes\n");
// 	scanf("%d%d",&n1&n2);

	printf(" Shortest distance 4 and 5 is %d ",findDistance(root,4,5));

	return 0;
}
