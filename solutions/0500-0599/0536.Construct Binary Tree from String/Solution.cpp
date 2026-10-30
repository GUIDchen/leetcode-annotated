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
// 题目：536. 从字符串生成二叉树（Construct Binary Tree from String）
// 思路：先取括号前的数字作为根，再用括号计数（遇 '(' 加一、遇 ')' 减一）切出两段完整的子树串，第一段是左孩子，第二段是右孩子。
// 时间复杂度：O(n^2)，每层递归都要重新切子串、重新扫描；空间复杂度：O(n)，递归栈与构造出的树。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    TreeNode* str2tree(string s) {  // s 是形如 "4(2(3)(1))(6(5))" 的字符串
        return dfs(s);  // 交给递归函数处理
    }

    TreeNode* dfs(string s) {  // 把一段字符串递归构造成子树
        if (s == "") return nullptr;  // 空串对应空子树，是递归出口
        int p = s.find("(");  // 找第一个左括号，它前面就是根节点的数字
        if (p == s.npos) return new TreeNode(stoi(s));  // 没有括号说明整串就是叶子节点的值
        TreeNode* root = new TreeNode(stoi(s.substr(0, p)));  // 括号前那段数字转成整数，作为当前子树的根
        int start = p;  // start 记录当前待切子串的左括号位置，初始指向第一个括号
        int cnt = 0;  // 括号计数器，用来判断一对括号是否已经闭合完整
        for (int i = p; i < s.size(); ++i) {  // 从第一个括号开始向后扫描
            if (s[i] == '(')  // 遇到左括号
                ++cnt;  // 未匹配的括号数加一
            else if (s[i] == ')')  // 遇到右括号
                --cnt;  // 未匹配的括号数减一
            if (cnt == 0) {  // 计数归零说明从 start 到 i 这一段括号已经配平
                if (start == p) {  // 还是第一次闭合，说明这是左孩子那一段
                    root->left = dfs(s.substr(start + 1, i - start - 1));  // 去掉最外层括号，递归构造左子树
                    start = i + 1;  // 下一段的起点挪到右括号之后
                } else  // 不是第一次闭合，那这一段属于右孩子（else 与 if 配对，无需大括号）
                    root->right = dfs(s.substr(start + 1, i - start - 1));  // 同样去掉外层括号，递归构造右子树
            }
        }
        return root;  // 返回构造好的当前子树
    }
};