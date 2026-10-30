// 题目：272. 最接近的二叉搜索树值 II（Closest Binary Search Tree Value II）
// 思路：对 BST 做中序遍历得到递增序列，用队列维护当前最优的 k 个值；队列满时若新值不比队首更近，则后面的值只会更远，直接剪枝。
// 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(k + h)，队列存 k 个值，递归栈深 h。
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
 */  // 判题器已提供 TreeNode 定义，这里只是注释说明，无需重复声明
class Solution {  // LeetCode 约定的题解类
public:  // 成员变量与两个方法都对外可见
    queue<int> q;  // 队列：按中序顺序保存最优的 k 个值，队首是其中离 target 最远的一个
    double target;  // 成员变量保存目标值，供 dfs 使用
    int k;  // 需要保留的元素个数

    vector<int> closestKValues(TreeNode* root, double target, int k) {  // 主入口：返回 BST 中离 target 最近的 k 个结点值
        this->target = target;  // 把入参 target 存到成员变量，避免给 dfs 增加参数
        this->k = k;  // 把入参 k 存到成员变量
        dfs(root);  // 中序遍历整棵树，边遍历边维护队列
        vector<int> ans;  // 收集最终答案
        while (!q.empty()) {  // 队列非空就逐个取出
            ans.push_back(q.front());  // 取出队首元素放入答案
            q.pop();  // 弹出队首
        }
        return ans;  // 返回 k 个最接近的值（按中序递增排列）
    }

    void dfs(TreeNode* root) {  // 中序遍历：BST 的中序结果是递增序列
        if (!root) return;  // 空结点直接返回
        dfs(root->left);  // 先递归左子树（更小的值）
        if (q.size() < k)  // 队列还没满，直接入队
            q.push(root->val);  // 入队当前值
        else {  // 队列已满：用当前值与队首（最远的一个）比较
            if (abs(root->val - target) >= abs(q.front() - target)) return;  // 不比队首更近就剪枝返回，因为中序后面只会更远
            q.pop();  // 弹出离 target 最远的队首
            q.push(root->val);  // 把更近的当前值入队
        }
        dfs(root->right);  // 继续遍历右子树
    }
};