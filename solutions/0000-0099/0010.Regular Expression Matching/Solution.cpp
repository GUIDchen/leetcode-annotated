// 题目：10. 正则表达式匹配（Regular Expression Matching）
// 思路：记忆化搜索，(i, j) 表示 s 从 i 起、p 从 j 起能否匹配；带 '*' 时在“用 0 次跳过”与“吃掉一个字符后原地继续”之间二选一。
// 时间复杂度：O(mn)，m、n 为两串长度，每个状态只算一次；空间复杂度：O(mn)，二维缓存数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isMatch(string s, string p) {  // s 是待匹配串，p 是含 '.' 与 '*' 的模式串
        int m = s.size(), n = p.size();  // 记录两串长度，递归中反复用到
        int f[m + 1][n + 1];  // 记忆化数组：0 未计算，1 可匹配，-1 不可匹配
        memset(f, 0, sizeof f);  // 全部清零，表示所有状态都还没算过
        function<bool(int, int)> dfs = [&](int i, int j) -> bool {  // 递归 lambda，按值捕获引用以便访问 s、p、f、m、n
            if (j >= n) {  // 模式串已用完
                return i == m;  // 原串也必须用完才算匹配
            }
            if (f[i][j]) {  // 该状态算过（值非 0）
                return f[i][j] == 1;  // 直接返回缓存结果，并把 -1 转成 false
            }
            int res = -1;  // 先假定不匹配
            if (j + 1 < n && p[j + 1] == '*') {  // 当前字符后接 '*'，表示可重复 0 次或多次
                if (dfs(i, j + 2) or (i < m and (s[i] == p[j] or p[j] == '.') and dfs(i + 1, j))) {  // 选择一：整段跳过 "x*"；选择二：吃掉 s[i] 后仍停在 j 继续用这个 x
                    res = 1;  // 任一分支成功即视为匹配
                }
            } else if (i < m and (s[i] == p[j] or p[j] == '.') and dfs(i + 1, j + 1)) {  // 普通单字符：字符相等或模式为 '.'，两边各后移一位
                res = 1;  // 单字符匹配成功
            }
            f[i][j] = res;  // 写入缓存，后续同状态直接查表
            return res == 1;  // 转成 bool 返回
        };
        return dfs(0, 0);  // 从两个串的开头开始匹配
    }
};
