// 题目：1382. 将二叉搜索树变平衡（Balance a Binary Search Tree）
// 思路：中序遍历 BST 得到升序数组，再用「每次取中点作根」的递归把数组重建成高度平衡的 BST。
// 时间复杂度：O(n)，遍历一次加建树一次；空间复杂度：O(n)，保存中序数组与递归栈。
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
public:  // 题解方法对外可见
    TreeNode* balanceBST(TreeNode* root) {  // root：原二叉搜索树的根节点
        dfs(root);  // 中序遍历，把 BST 中的键值按升序收集进 nums
        return build(0, nums.size() - 1);  // 用整个有序数组递归重建平衡 BST 并返回新根
    }  // balanceBST 结束

private:  // 以下为辅助成员
    vector<int> nums;  // 中序遍历结果，天然是升序序列

    void dfs(TreeNode* root) {  // 中序遍历：左子树 → 根 → 右子树
        if (!root) {  // 遇到空节点
            return;  // 直接返回，递归出口
        }  // 空节点判断结束
        dfs(root->left);  // 先递归处理左子树，保证更小的值先被访问
        nums.push_back(root->val);  // 再访问根节点，把键值追加到数组末尾
        dfs(root->right);  // 最后递归处理右子树
    }  // dfs 结束

    TreeNode* build(int i, int j) {  // 把 nums[i..j] 这段升序区间构造成平衡 BST
        if (i > j) {  // 区间为空，说明没有节点可建
            return nullptr;  // 返回空指针作为叶子
        }  // 区间判断结束
        int mid = (i + j) >> 1;  // 取中点作为根，使左右两部分规模尽量相等
        TreeNode* left = build(i, mid - 1);  // 递归构造左子树（更小的那半段）
        TreeNode* right = build(mid + 1, j);  // 递归构造右子树（更大的那半段）
        return new TreeNode(nums[mid], left, right);  // 以中点为根，挂上左右子树
    }  // build 结束
};  // Solution 类结束