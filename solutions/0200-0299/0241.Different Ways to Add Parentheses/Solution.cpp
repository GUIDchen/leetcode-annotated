// 题目：241. 为运算表达式设计优先级（Different Ways to Add Parentheses）
// 思路：分治 + 记忆化。枚举每个运算符作为最后一次运算，把表达式切成左右两段递归求解，再两两组合结果。
// 时间复杂度：O(结果数量) 量级，记忆化后每个子表达式只算一次；空间复杂度：O(不同子表达式个数) 的记忆化表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> diffWaysToCompute(string expression) {  // expression：由数字与 + - * 组成的表达式
        return dfs(expression);  // 交给带记忆化的递归求解
    }

    vector<int> dfs(string exp) {  // exp：当前子表达式，返回它能算出的所有结果
        if (memo.count(exp)) return memo[exp];  // 记忆化：该子表达式算过就直接复用，避免重复递归
        if (exp.size() < 3) return {stoi(exp)};  // 长度不足 3 说明只剩一个数，无法再分，直接返回它
        vector<int> ans;  // 收集当前子表达式的所有可能结果
        int n = exp.size();  // 子表达式长度
        for (int i = 0; i < n; ++i) {  // 枚举每个字符，尝试让它作为最后一次运算的运算符
            char c = exp[i];  // 当前字符
            if (c == '-' || c == '+' || c == '*') {  // 只有运算符才能把表达式切成两段
                vector<int> left = dfs(exp.substr(0, i));  // 递归求左半部分的所有结果
                vector<int> right = dfs(exp.substr(i + 1, n - i - 1));  // 递归求右半部分的所有结果
                for (int& a : left) {  // 左半部分的每个结果
                    for (int& b : right) {  // 与右半部分的每个结果两两组合
                        if (c == '-')  // 运算符是减法
                            ans.push_back(a - b);  // 记录一种 a - b 的结果
                        else if (c == '+')  // 运算符是加法
                            ans.push_back(a + b);  // 记录一种 a + b 的结果
                        else  // 剩下只可能是乘法
                            ans.push_back(a * b);  // 记录一种 a * b 的结果
                    }
                }
            }
        }
        memo[exp] = ans;  // 记忆化：缓存当前子表达式的全部结果
        return ans;  // 返回当前子表达式的全部结果
    }

private:  // 以下为内部实现
    unordered_map<string, vector<int>> memo;  // 记忆化表：子表达式文本 → 它的所有可能计算结果
};