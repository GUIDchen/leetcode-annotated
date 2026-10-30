// 题目：2792. 计算足够大的节点数（Count Nodes That Are Great Enough）
// 思路：后序 dfs 返回「子树中前 k 小的值」组成的大根堆（堆顶即第 k 小），堆大小为 k 且堆顶小于当前节点值时当前节点足够大。
// 时间复杂度：O(n * k log k)，每个节点合并左右两个大小为 k 的堆；空间复杂度：O(n + 递归深度 * k)，递归栈与堆存储的开销。
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
    int countGreatEnoughNodes(TreeNode* root, int k) {  // root：二叉树根节点；k：题目要求的排名 k
        int ans = 0;  // ans：足够大的节点个数
        function<priority_queue<int>(TreeNode*)> dfs = [&](TreeNode* root) {  // dfs 返回「子树中前 k 小的值」组成的大根堆，堆顶是这 k 个数中最大的（即第 k 小）
            if (!root) {  // 空节点没有值
                return priority_queue<int>();  // 返回空堆
            }  // if 结束
            auto left = dfs(root->left);  // 递归求左子树的候选堆
            auto right = dfs(root->right);  // 递归求右子树的候选堆
            while (right.size()) {  // 把右子树的候选值逐个并入左堆，合并后仍只保留最小的 k 个
                left.push(right.top());  // 取出右堆的堆顶（其中最大的那个）并入左堆；循环会把右堆全部转移过去
                right.pop();  // 弹出已转移的堆顶，避免重复处理
                if (left.size() > k) {  // 左堆超过 k 个时
                    left.pop();  // 丢掉左堆中最大的元素，保证堆里始终是最小的 k 个
                }  // if 结束
            }  // while 结束
            if (left.size() == k && left.top() < root->val) {  // 左堆恰好装满 k 个值时，堆顶就是子树中的第 k 小值
                ++ans;  // 第 k 小值小于当前节点值，说明当前节点足够大，答案加一
            }  // if 结束
            left.push(root->val);  // 把当前节点值也加入堆，作为候选上传给父节点
            if (left.size() > k) {  // 同样维持堆中最多 k 个元素
                left.pop();  // 超出 k 个时弹出最大的元素
            }  // if 结束
            return left;  // 返回包含子树前 k 小值的大根堆
        };  // lambda 定义结束
        dfs(root);  // 从根节点开始后序遍历
        return ans;  // 返回足够大的节点数
    }  // 方法结束
};  // 类定义结束