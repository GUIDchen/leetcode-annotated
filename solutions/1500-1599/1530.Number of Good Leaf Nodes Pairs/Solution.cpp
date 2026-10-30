// 题目：1530. 好叶子节点对的数量（Number of Good Leaf Nodes Pairs）
// 思路：在递归过程中，以每个结点为「汇合点」，分别统计左右子树中各距离的叶子个数，再用 i+j<=distance 组合配对。
// 时间复杂度：O(n·distance²)，每个结点合并左右距离表；空间复杂度：O(n)，递归栈与距离表开销。
/**  // 下面这段是题面给出的二叉树结点定义，无需自己实现
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
    int countPairs(TreeNode* root, int distance) {  // root：二叉树根结点；distance：叶子对之间允许的最大距离
        if (!root) return 0;  // 空树没有叶子，自然没有叶子对
        int ans = countPairs(root->left, distance) + countPairs(root->right, distance);  // 先递归统计左、右子树内部各自的好叶子对，路径不经过 root
        vector<int> cnt1(distance);  // cnt1[k]：左子树中距离 root 为 k 的叶子个数，下标最多到 distance-1
        vector<int> cnt2(distance);  // cnt2[k]：右子树中距离 root 为 k 的叶子个数
        dfs(root->left, cnt1, 1);  // 从 root 的左孩子开始收集左子树叶子，root 到孩子的距离记为 1
        dfs(root->right, cnt2, 1);  // 同样收集右子树的叶子，距离从 1 开始计
        for (int i = 0; i < distance; ++i) {  // 枚举左叶子的距离 i
            for (int j = 0; j < distance; ++j) {  // 枚举右叶子的距离 j
                if (i + j <= distance) {  // 一个左叶子与一个右叶子的路径经过 root，长度恰为 i+j；不超过 distance 才算好叶子对
                    ans += cnt1[i] * cnt2[j];  // 距离为 i 和 j 的叶子可以两两组合，个数相乘后累加
                }  // if 分支结束
            }  // 内层距离枚举结束
        }  // 外层距离枚举结束
        return ans;  // 返回「子树内部」与「跨 root 配对」的总数
    }  // countPairs 方法结束

    void dfs(TreeNode* root, vector<int>& cnt, int i) {  // 辅助函数：从 root 出发、当前距离为 i，把所有叶子计入 cnt[i]
        if (!root || i >= cnt.size()) return;  // 空结点，或距离已≥distance（再远也不会被配对），直接剪枝
        if (!root->left && !root->right) {  // 左右孩子都为空，说明当前结点就是叶子
            ++cnt[i];  // 距离为 i 的叶子数量加一
            return;  // 叶子没有孩子，递归到此为止
        }  // 叶子分支结束
        dfs(root->left, cnt, i + 1);  // 继续深入左子树，距离加一
        dfs(root->right, cnt, i + 1);  // 继续深入右子树，距离加一
    }  // dfs 辅助函数结束
};  // 题解类结束