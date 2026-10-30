// 题目：471. 编码最短长度的字符串（Encode String with Shortest Length）
// 思路：区间 DP。f[i][j] 存 s[i..j] 的最短编码；先用 KMP 思想找最小周期把整段折叠成 k[子串]，再枚举切分点比较拼接长度取更短者。
// 时间复杂度：O(n^4)，区间 O(n^2) × 切分 O(n) × 子串查找 O(n)；空间复杂度：O(n^2)，存所有区间的字符串结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string encode(string s) {  // s 是待编码的原始字符串，返回它的最短压缩表示
        int n = s.size();  // 字符串长度，作为 DP 的规模
        vector<vector<string>> f(n, vector<string>(n));  // f[i][j] 记录子串 s[i..j] 的最短编码结果

        auto g = [&](int i, int j) {  // 辅助 lambda：尝试把整段 s[i..j] 折叠成「次数[子串]」的形式
            string t = s.substr(i, j - i + 1);  // 取出当前区间的原始子串
            if (t.size() < 5) {  // 折叠后的最短形态是 a[b]，至少要 4 个字符，长度不足 5 时折叠不会变短
                return t;  // 直接返回原文，省掉无效的折叠尝试
            }
            int k = (t + t).find(t, 1);  // 在 t+t 中从下标 1 开始查找 t，得到的 k 就是最小周期长度（找不到则为 size）
            if (k < t.size()) {  // k 小于长度说明 t 由若干等长块重复拼成，可以折叠
                int cnt = t.size() / k;  // 重复次数 = 总长度 / 最小周期长度
                return to_string(cnt) + "[" + f[i][i + k - 1] + "]";  // 次数 + 方括号，方括号里放「一个周期的最短编码」（可继续折叠）
            }
            return t;  // 无法折叠，只能返回原文
        };

        for (int i = n - 1; ~i; --i) {  // 左端点从右往左枚举，保证依赖的更短区间已经算好
            for (int j = i; j < n; ++j) {  // 右端点从左往右枚举，区间长度由短到长
                f[i][j] = g(i, j);  // 方案一：整段折叠（或原样返回）
                if (j - i + 1 > 4) {  // 长度不超过 4 时切分不可能更短，直接跳过
                    for (int k = i; k < j; ++k) {  // 枚举切分点，把区间拆成 [i,k] 与 [k+1,j]
                        string t = f[i][k] + f[k + 1][j];  // 方案二：两段各自的最短编码直接拼接
                        if (t.size() < f[i][j].size()) {  // 拼接结果更短才更新答案
                            f[i][j] = t;  // 记录更优的编码
                        }
                    }
                }
            }
        }
        return f[0][n - 1];  // 整个字符串的最短编码
    }
};