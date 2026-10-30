// 题目：988. 从叶结点开始的最小字符串（Smallest String Starting From Leaf）
// 思路：从根 DFS，路径记录根到当前结点的字母；到叶子时反转成叶→根字符串，取字典序最小。
// 时间复杂度：O(n^2)，n 为结点数，每条根到叶路径的复制反转与比较都需 O(n)；空间复杂度：O(n)，递归栈与路径字符串。
// 下面是题目给出的二叉树结点定义，实际判题时由 LeetCode 提供，无需自己写。
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
    string ans = "";  // 全局答案：保存当前找到的字典序最小字符串，空串表示还没遇到任何叶子

    string smallestFromLeaf(TreeNode* root) {  // 入口：root 是二叉树根结点；返回从叶到根拼接出的最小字符串
        string path = "";  // 当前 DFS 路径，内容是从根到当前结点的字母（正向顺序）
        dfs(root, path);  // 从根开始深度优先搜索所有根到叶的路径
        return ans;  // 搜索结束后 ans 就是答案，直接返回
    }

    void dfs(TreeNode* root, string& path) {  // 递归：沿路记录字母；path 用引用传递，回溯时统一 pop 撤销
        if (!root) return;  // 空结点直接返回，避免访问空指针
        path += 'a' + root->val;  // 把结点值 0..25 映射成字母 'a'..'z' 并追加到路径末尾
        if (!root->left && !root->right) {  // 叶子判断：左右儿子都为空，说明此时 path 是一条完整的根到叶路径
            string t = path;  // 复制一份路径，避免反转时破坏原来的 path
            reverse(t.begin(), t.end());  // 反转成「从叶到根」的方向，与题目要求一致
            if (ans == "" || t < ans) ans = t;  // 更新答案：第一个叶子直接取，之后取字典序更小的那个
        }  // 叶子分支结束
        dfs(root->left, path);  // 继续深入左子树
        dfs(root->right, path);  // 继续深入右子树
        path.pop_back();  // 回溯：撤销本层追加的字母，把 path 恢复成进入本层前的样子
    }  // dfs 函数结束
};  // 类定义结束