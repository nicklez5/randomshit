#include <iostream>
#include <vector>

using namespace std;

struct TreeNode{
	vector<string> token_stringz;
	vector<int> token_num_types;
	TreeNode* left;
	TreeNode* right;
	TreeNode(vector<string> token_str, vector<int> token_type, TreeNode* _left, TreeNode* _right);
};
TreeNode::TreeNode(){
	left = NULL;
	right = NULL;
}
TreeNode::TreeNode(vector<string> token_str, vector<int> token_type){
	left = NULL;
	right = NULL;
	token_stringz = token_str;
	token_num_typez = token_type;
}
TreeNode::TreeNode(vector<string> token_str, vector<int> token_type, TreeNode* _left = NULL, TreeNode* _right = NULL){
	token_stringz = token_str;
	token_num_types = token_type;
	left = _left;
	right = _right;
}
	
