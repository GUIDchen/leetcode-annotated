// 题目：1305. 两棵二叉搜索树中的所有元素（All Elements in Two Binary Search Trees）
// 核心思路：中序遍历两棵 BST 分别得到升序数组，再用双指针归并成一个升序数组。
// 时间复杂度：O(m + n)，m、n 为两棵树的节点数；空间复杂度：O(m + n)，用于存放两个中序数组和答案。
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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {  // root1、root2 是两棵 BST 的根
        vector<int> a, b, ans;  // a、b 存两棵树的中序序列，ans 存最终归并结果
        dfs(root1, a);  // 中序遍历第一棵树，把升序结果写入 a
        dfs(root2, b);  // 中序遍历第二棵树，把升序结果写入 b

        int i = 0, j = 0;  // i、j 分别是 a、b 的读指针
        while (i < a.size() && j < b.size()) {  // 两边都还有元素时做归并
            if (a[i] <= b[j]) {  // 取较小的一方，保证答案整体升序
                ans.push_back(a[i++]);  // 放入 a[i]，并把 i 后移一位
            } else {
                ans.push_back(b[j++]);  // 放入 b[j]，并把 j 后移一位
            }
        }
        while (i < a.size()) {  // a 中剩余元素全部追加到答案末尾
            ans.push_back(a[i++]);  // 逐个放入并移动指针
        }
        while (j < b.size()) {  // b 中剩余元素全部追加到答案末尾
            ans.push_back(b[j++]);  // 逐个放入并移动指针
        }
        return ans;  // 返回升序合并后的所有元素
    }

private:  // 以下辅助函数只供类内部调用
    void dfs(TreeNode* root, vector<int>& nums) {  // 中序遍历：左子树 → 根 → 右子树
        if (root == nullptr) {  // 空节点没有元素可访问
            return;  // 直接回溯
        }
        dfs(root->left, nums);  // 先递归左子树，保证较小值先被收集
        nums.push_back(root->val);  // 再访问根节点，把当前值追加到 nums
        dfs(root->right, nums);  // 最后递归右子树
    }
};
