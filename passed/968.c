//
// Created by zhuoran liu on 2021/2/20.
//


int temp(struct TreeNode* root, int* res) {
    if (!root) return 2;
    int left = temp(root->left, res), right = temp(root->right, res);
    if (left == 0 || right == 0) {
        (*res)++;
        return 1;
    }
    return left == 1 || right == 1 ? 2 : 0;

}

int minCameraCover(struct TreeNode* root){
    int res = 0;
    return (temp(root, &res) == 0 ? 1 : 0) + res;
}