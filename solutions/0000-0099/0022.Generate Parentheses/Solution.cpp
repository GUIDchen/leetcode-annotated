// 题目：22. 括号生成（Generate Parentheses）
// 思路：回溯 DFS，状态只记录已用的左括号数 l、右括号数 r；剪掉 l>n、r>n 以及 l<r（右括号多于左括号）的分支。
// 时间复杂度：O(C_n)，即第 n 个卡特兰数级别的合法方案数（乘每条方案的复制代价）；空间复杂度：O(n)，递归深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> generateParenthesis(int n) {  // n：括号对数
        vector<string> ans;  // 收集所有合法括号组合
        auto dfs = [&](this auto&& dfs, int l, int r, string t) -> void {  // C++23 显式对象参数：让 lambda 能以值/引用显式传自己实现递归
            if (l > n || r > n || l < r) {  // 左或右括号超过 n，或右括号比左括号多，都是非法前缀
                return;  // 剪枝，不再往下搜索
            }
            if (l == n && r == n) {  // 左右括号都用满，得到一个完整合法方案
                ans.push_back(t);  // 记录这条方案
                return;  // 无需继续扩展
            }
            dfs(l + 1, r, t + "(");  // 分支一：再放一个左括号
            dfs(l, r + 1, t + ")");  // 分支二：再放一个右括号
        };
        dfs(0, 0, "");  // 从「一个括号都没用、串为空」开始搜索
        return ans;  // 返回全部合法组合
    }
};
