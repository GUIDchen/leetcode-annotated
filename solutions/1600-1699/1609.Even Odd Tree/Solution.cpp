// 题目：1609. 奇偶树（Even Odd Tree）
// 思路：BFS 逐层遍历，用 prev 记录同层上一个值；偶数层要求「奇数且严格递增」，奇数层要求「偶数且严格递减」，任一层违反即返回 false。
// 时间复杂度：O(n)，每个节点只入队出队一次；空间复杂度：O(n)，队列最宽时存放一整层节点。
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
class Solution {  // 题解类
public:  // 对外接口
    bool isEvenOddTree(TreeNode* root) {  // root 为二叉树根节点
        int even = 1;  // even 为 1 表示当前处理的是偶数层（从 0 开始数的第 0、2、4… 层）
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放入根节点
        while (!q.empty()) {  // 队列非空就继续逐层处理
            int prev = even ? 0 : 1e7;  // 本层比较用的「前一个值」：偶数层要递增，从最小值 0 起；奇数层要递减，从足够大的数起
            for (int n = q.size(); n; --n) {  // 循环开始时队列里恰好是本层全部节点，故本层处理 n 次
                root = q.front();  // 取出队首节点
                q.pop();  // 出队
                if (even && (root->val % 2 == 0 || prev >= root->val)) {  // 偶数层要求节点值为奇数且严格递增；% 2 == 0 表示是偶数，prev >= 当前值表示没有严格递增
                    return false;  // 违反条件，不是奇偶树，立即返回 false
                }  // 偶数层判断结束
                if (!even && (root->val % 2 == 1 || prev <= root->val)) {  // 奇数层要求节点值为偶数且严格递减；% 2 == 1 表示是奇数，prev <= 当前值表示没有严格递减
                    return false;  // 违反条件，立即返回 false
                }  // 奇数层判断结束
                prev = root->val;  // 更新前一个值，供同层下一个节点比较
                if (root->left) {  // 左孩子存在就入队，留到下一层处理
                    q.push(root->left);  // 左孩子入队
                }  // 左孩子判断结束
                if (root->right) {  // 右孩子存在就入队
                    q.push(root->right);  // 右孩子入队
                }  // 右孩子判断结束
            }  // 本层节点处理完毕
            even ^= 1;  // 切换层号的奇偶：偶数层之后是奇数层，反之亦然
        }  // while 循环结束
        return true;  // 所有层都满足要求，返回 true
    }
};