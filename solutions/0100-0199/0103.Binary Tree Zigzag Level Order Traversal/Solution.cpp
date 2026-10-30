// 题目：103. 二叉树的锯齿形层序遍历（Binary Tree Zigzag Level Order Traversal）
// 思路：仍是 BFS 分层，只是偶数层（从 1 计）先按自左向右收集，再翻转该层结果，形成左右交替的锯齿。
// 时间复杂度：O(n)，每个节点进出队各一次，翻转总代价也是线性；空间复杂度：O(w)，w 为最大层宽。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x, left), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {  // root：树根，返回锯齿形（左右交替）的分层序列
        vector<vector<int>> ans;  // 答案：每个元素是某一层的值序列
        if (!root) {  // 空树
            return ans;  // 没有层可遍历，返回空答案
        }
        queue<TreeNode*> q{{root}};  // BFS 队列，初始放入根节点
        int left = 1;  // 方向标记：1 表示本层自左向右输出，0 表示自右向左
        while (!q.empty()) {  // 队列非空表示还有层要处理
            vector<int> t;  // 暂存本层节点值（统一按自左向右收集）
            for (int n = q.size(); n; --n) {  // 先用当前队列长度锁定本层节点数，保证只处理本层
                auto node = q.front();  // 取队首节点
                q.pop();  // 弹出，避免重复
                t.emplace_back(node->val);  // 就地构造，把该节点值加入本层结果
                if (node->left) {  // 左孩子存在
                    q.push(node->left);  // 左孩子入队，等待下一层处理
                }
                if (node->right) {  // 右孩子存在
                    q.push(node->right);  // 右孩子入队，保持下一层的自左向右顺序
                }
            }
            if (!left) {  // 当前层要求自右向左
                reverse(t.begin(), t.end());  // 直接翻转自左向右收集的结果即可得到反序
            }
            ans.emplace_back(t);  // 把处理好的本层结果加入答案，避免一次拷贝
            left ^= 1;  // 与 1 异或实现 0/1 翻转，切换下一层的输出方向
        }
        return ans;  // 返回锯齿形层序遍历结果
    }
};