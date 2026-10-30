// 题目：301. 删除无效的括号（Remove Invalid Parentheses）
// 思路：先扫描一次算出必须删掉的左、右括号个数；再 DFS 枚举「删当前括号 / 保留当前括号」两种分支，配合剩余字符数与右括号前缀两个剪枝。
// 时间复杂度：O(n · 2^n)，最坏情况枚举每个括号删或不删；空间复杂度：O(n + k)，递归栈深度 n、结果集存 k 个解。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> removeInvalidParentheses(string s) {  // s：含括号的字符串；返回所有删除次数最少的合法结果
        unordered_set<string> ans;  // 用 set 去重，避免不同删除路径产生相同字符串
        int l = 0, r = 0, n = s.size();  // l、r：还需删除的左、右括号个数；n：串长
        for (char& c : s) {  // 一次扫描统计至少要删掉多少个左、右括号
            if (c == '(') {  // 遇到左括号
                ++l;  // 需要的左括号数加一
            } else if (c == ')') {  // 遇到右括号
                if (l) {  // 前面有可匹配的左括号
                    --l;  // 配对成功，消耗掉一个左括号
                } else {  // 前面没有可匹配的左括号
                    ++r;  // 这个右括号是多出来的，必须删除
                }  // if/else 结束
            }  // if/else 结束
        }  // for 循环结束
        function<void(int, int, int, int, int, string)> dfs;  // 先声明递归函数类型，lambda 才能捕获并引用自身
        dfs = [&](int i, int l, int r, int lcnt, int rcnt, string t) {  // i：当前下标；l/r：剩余需删数；lcnt/rcnt：已保留的左右括号数；t：当前构造的串
            if (i == n) {  // 已经走到字符串末尾
                if (l == 0 && r == 0) {  // 该删的括号都删完了，说明这是一个合法解
                    ans.insert(t);  // 加入结果集（set 自动去重）
                }  // if 块结束
                return;  // 递归边界返回
            }  // if 块结束
            if (n - i < l + r || lcnt < rcnt) {  // 剪枝：剩余字符不够删，或已保留的右括号多于左括号
                return;  // 此分支不可能产生合法解，直接剪掉
            }  // if 块结束
            if (s[i] == '(' && l) {  // 当前字符是左括号且还需要删左括号，尝试删除它
                dfs(i + 1, l - 1, r, lcnt, rcnt, t);  // 删除数减一后继续往下搜索
            }  // if 块结束
            if (s[i] == ')' && r) {  // 当前字符是右括号且还需要删右括号，尝试删除它
                dfs(i + 1, l, r - 1, lcnt, rcnt, t);  // 删除数减一后继续往下搜索
            }  // if 块结束
            int x = s[i] == '(' ? 1 : 0;  // 当前字符是左括号则记 1，否则记 0
            int y = s[i] == ')' ? 1 : 0;  // 当前字符是右括号则记 1，否则记 0
            dfs(i + 1, l, r, lcnt + x, rcnt + y, t + s[i]);  // 另一个分支：保留当前字符，把它计入左右括号计数
        };  // lambda 定义结束

        dfs(0, l, r, 0, 0, "");  // 从下标 0、空串开始搜索所有删除方案
        return vector<string>(ans.begin(), ans.end());  // 把 set 转成 vector 返回
    }  // 方法结束
};  // 类定义结束