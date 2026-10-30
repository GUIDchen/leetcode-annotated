// 题目：663. 均匀树划分（Equal Tree Partition）
// 思路：后序 DFS 求每个节点为根的子树和并记录；整棵树总和为偶数、且某个「真子树」的和等于总和一半时可切分。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈与 seen 数组各为 O(n)。
// 下面这段是 LeetCode 题面给出的 TreeNode 定义，判题器会自动注入，无需自己补。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 公有接口
    vector<int> seen;  // seen 收集 DFS 过程中每个节点为根的子树和

    bool checkEqualTree(TreeNode* root) {  // root 是树根，判断能否删掉一条边把树分成和相等的两部分
        int s = sum(root);  // 先求整棵树的总和，同时把所有子树和都写进 seen
        if (s % 2 != 0) return false;  // 总和是奇数就不可能平分，直接返回 false
        seen.pop_back();  // 弹出根节点的子树和：只有「真子树」才能被切下来，整棵树整体不算
        return count(seen.begin(), seen.end(), s / 2);  // 存在真子树和等于总和一半即可切分（count 为个数，非 0 即真）
    }  // 结束 checkEqualTree

    int sum(TreeNode* root) {  // 后序遍历：求以 root 为根的子树和
        if (!root) return 0;  // 空节点子树和为 0
        int l = sum(root->left), r = sum(root->right);  // 先递归求左右子树的子树和
        int s = l + r + root->val;  // 当前子树和 = 左子树和 + 右子树和 + 根节点值
        seen.push_back(s);  // 记录当前子树和，供外层判断能否平分
        return s;  // 把当前子树和返回给父节点
    }  // 结束 sum
};