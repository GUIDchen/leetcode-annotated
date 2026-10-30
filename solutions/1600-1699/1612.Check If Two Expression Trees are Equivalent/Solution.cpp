// 题目：1612. 检查两棵二叉表达式树是否等价（Check If Two Expression Trees are Equivalent）
// 思路：中序遍历两棵树，用 cnt 统计每个操作数的净系数（第一棵 +1、第二棵 -1）；加法可交换可结合，最终全为 0 即等价。
// 时间复杂度：O(n)，两棵树各遍历一次；空间复杂度：O(n)，递归栈最深为树的深度，计数数组只占 26 个位置。
/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkEquivalence(Node* root1, Node* root2) {  // root1/root2：两棵表达式树的根节点
        int cnt[26]{};  // 计数数组：下标 0~25 对应操作数 'a'~'z' 的净出现次数，{} 零初始化
        function<void(Node*, int)> dfs = [&](Node* root, int v) {  // 递归中序遍历；v 是这棵树贡献的符号（+1 / -1）
            if (!root) {  // 空节点，递归到边界
                return;  // 直接返回上一层
            }
            if (root->val != '+') {  // 非 '+' 说明是叶子操作数（题目保证只有 '+' 和小写字母）
                cnt[root->val - 'a'] += v;  // 用字符差值映射到 0~25，并按符号累加净系数
            }
            dfs(root->left, v);  // 递归处理左子树，符号保持不变
            dfs(root->right, v);  // 递归处理右子树，符号保持不变
        };
        dfs(root1, 1);  // 第一棵树整体记 +1，表示「被减数」
        dfs(root2, -1);  // 第二棵树整体记 -1，表示「减数」
        for (int& x : cnt) {  // 遍历所有字母的净系数
            if (x) {  // 只要有一个字母净系数不为 0，说明两式展开后不同
                return false;  // 不等价
            }
        }
        return true;  // 全部抵消为 0，两棵表达式树等价
    }
};