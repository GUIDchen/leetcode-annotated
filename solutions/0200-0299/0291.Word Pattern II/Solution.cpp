// 题目：291. 单词规律 II（Word Pattern II）—— pattern 每个字符要对应 s 的一个非空子串，且映射是双射，判断是否存在这种切分。
// 核心思路：回溯 DFS。按 pattern 的字符顺序枚举切分长度，用 d（字符→串）与 vis（已用过的串）保证双射，失败立即回退。
// 时间复杂度：最坏指数级（每层都有多种切分，靠长度剪枝削减），约为 O(n^m)；空间复杂度：O(m + n)，递归栈加两张哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool wordPatternMatch(string pattern, string s) {  // pattern：规律串；s：等待切分的字符串
        unordered_set<string> vis;  // 已被某个 pattern 字符占用的子串，保证不同字符不会映射到同一个串
        unordered_map<char, string> d;  // pattern 字符 -> 已确定的子串
        return dfs(0, 0, pattern, s, vis, d);  // 从 pattern 第 0 位、s 第 0 位开始深度优先搜索
    }

    bool dfs(int i, int j, string& p, string& s, unordered_set<string>& vis, unordered_map<char, string>& d) {  // i：pattern 下标；j：s 下标；返回从这两个位置开始能否匹配
        int m = p.size(), n = s.size();  // 两个串的长度
        if (i == m && j == n) return true;  // 两边同时用完，说明找到了一组合法映射
        if (i == m || j == n || m - i > n - j) return false;  // 一方提前用完，或剩余字符数多于剩余长度（每个子串至少 1 个字符）→ 剪枝
        char c = p[i];  // 当前要处理的 pattern 字符
        for (int k = j + 1; k <= n; ++k) {  // 枚举该字符对应子串的右端点；子串非空，所以从 j+1 开始
            string t = s.substr(j, k - j);  // 本次尝试的子串 s[j .. k-1]
            if (d.count(c) && d[c] == t) {  // c 已有映射且正好等于 t：沿用旧映射，继续匹配下一个字符
                if (dfs(i + 1, k, p, s, vis, d)) return true;  // 递归匹配剩余部分，成功即整体成功
            }
            if (!d.count(c) && !vis.count(t)) {  // c 还没映射，且 t 也没被别的字符占用 → 可以建立一条新映射
                d[c] = t;  // 记录正向映射
                vis.insert(t);  // 标记该子串已被占用
                if (dfs(i + 1, k, p, s, vis, d)) return true;  // 递归尝试后续匹配
                vis.erase(t);  // 回溯：撤销子串占用
                d.erase(c);  // 回溯：撤销字符映射
            }
        }
        return false;  // 所有切分方式都失败
    }
};