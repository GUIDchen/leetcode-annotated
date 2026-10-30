// 题目：2800. 包含三个字符串的最短字符串（Shortest String That Contains Three Strings）
// 思路：枚举 a、b、c 的 6 种拼接顺序，用 f 求两个串的最短「合并串」，按长度、字典序取最优。
// 时间复杂度：O(L^2)，L 为串长（f 最多比较 L 次、每次 O(L)）；空间复杂度：O(L)，用于存放候选串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string minimumString(string a, string b, string c) {  // a、b、c：三个待包含的字符串
        vector<string> s = {a, b, c};  // 把三个串放进数组，方便按下标取用
        vector<vector<int>> perm = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {2, 0, 1}};  // 三个串的全部 6 种拼接顺序
        string ans = "";  // 当前最优答案，空串表示还没找到
        for (auto& p : perm) {  // 逐个尝试每一种拼接顺序
            int i = p[0], j = p[1], k = p[2];  // 拆出本次顺序对应的三个下标
            string t = f(f(s[i], s[j]), s[k]);  // 先把前两个合并，再与第三个合并，得到候选答案
            if (ans == "" || t.size() < ans.size() || (t.size() == ans.size() && t < ans)) {  // 更短，或等长但字典序更小
                ans = t;  // 更新最优答案
            }
        }
        return ans;  // 返回最短且字典序最小的合并串
    }

    string f(string s, string t) {  // 求同时包含 s 与 t 的最短合并串（s 在前、t 在后的顺序）
        if (s.find(t) != string::npos) {  // t 已经是 s 的子串
            return s;  // 那么 s 本身就包含了 t，直接返回 s
        }
        if (t.find(s) != string::npos) {  // s 已经是 t 的子串
            return t;  // 那么 t 本身就包含了 s，直接返回 t
        }
        int m = s.size(), n = t.size();  // m、n：两个串的长度
        for (int i = min(m, n); i; --i) {  // 从可能的最大重叠长度开始递减，找最长的「s 后缀 = t 前缀」
            if (s.substr(m - i) == t.substr(0, i)) {  // s 长度为 i 的后缀与 t 长度为 i 的前缀相同
                return s + t.substr(i);  // 保留重叠部分，只把 t 多出来的部分接在后面
            }
        }
        return s + t;  // 没有任何重叠，直接首尾相接
    };
};