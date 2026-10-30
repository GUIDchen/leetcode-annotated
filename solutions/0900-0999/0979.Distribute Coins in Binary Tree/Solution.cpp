// 题目：979. 在二叉树中分配硬币（Distribute Coins in Binary Tree）
// 思路：后序遍历返回子树需要向外「净输出」的硬币数，每个子树的盈余绝对值之和就是必须经过这条边的移动次数。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，递归栈深度。
// 题目给出的二叉树节点定义：val 是该节点的硬币数，left/right 分别指向左右孩子
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
    int distributeCoins(TreeNode* root) {  // root：二叉树根节点，返回让每个节点恰好有 1 枚硬币所需的最少移动次数
        int ans = 0;  // ans 累计所有边上发生的移动次数
        function<int(TreeNode*)> dfs = [&](TreeNode* root) -> int {  // 后序 DFS lambda：返回以 root 为根的子树需要净输出的硬币数（负数表示需要净输入）
            if (!root) {  // 空节点没有硬币可搬
                return 0;  // 空节点贡献 0
            }  // if 结束
            int left = dfs(root->left);  // 先递归左子树，拿到左子树需要净输出/净输入的硬币数
            int right = dfs(root->right);  // 再递归右子树，拿到右子树需要净输出/净输入的硬币数
            ans += abs(left) + abs(right);  // 左、右子树与当前节点之间的硬币都要经过这两条边，绝对值之和就是移动次数
            return left + right + root->val - 1;  // 本子树净输出量 = 左 + 右 + 自身硬币数 - 自己保留的 1 枚
        };  // lambda 定义结束
        dfs(root);  // 从根开始后序遍历，过程即完成全部统计
        return ans;  // 返回最少移动次数
    }  // 题解方法结束
};  // Solution 类结束