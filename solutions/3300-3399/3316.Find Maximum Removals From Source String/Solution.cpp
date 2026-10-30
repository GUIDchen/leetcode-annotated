// 题目：3316. 从原字符串里进行删除操作的最多次数（Find Maximum Removals From Source String）
// 核心思路：在 source 上做「子序列匹配 + 能删就删」的 DP：f[i][j] 表示用 source 前 i 个字符匹配 pattern 前 j 个字符时最多能删掉的字符数，删一个可删字符得分 1，用字符去匹配则不得分。
// 时间复杂度：O(m·n)，m、n 为两个串长度；空间复杂度：O(m·n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {  // source：原串；pattern：必须留下的子序列；targetIndices：允许删除的下标集合
        int m = source.length(), n = pattern.length();  // m、n 分别是 source 与 pattern 的长度
        vector<vector<int>> f(m + 1, vector<int>(n + 1, INT_MIN / 2));  // DP 表，初值取极小值表示不可达（用 INT_MIN/2 是为避免加法下溢）
        f[0][0] = 0;  // 空串匹配空串，删除次数为 0

        vector<int> s(m);  // s[i] 标记 source 中下标 i 的字符是否允许被删除
        for (int i : targetIndices) {  // 遍历所有允许删除的下标
            s[i] = 1;  // 把这些位置标记为可删（1 同时也是删掉它能得到的分数）
        }  // 标记结束

        for (int i = 1; i <= m; ++i) {  // 逐个考虑 source 的字符
            for (int j = 0; j <= n; ++j) {  // j 表示当前已经匹配到 pattern 的前 j 个字符
                f[i][j] = f[i - 1][j] + s[i - 1];  // 选择一：删掉 source[i-1]，可删则得分加一（不可删则加 0，相当于保留）
                if (j > 0 && source[i - 1] == pattern[j - 1]) {  // 选择二：用 source[i-1] 去匹配 pattern[j-1]
                    f[i][j] = max(f[i][j], f[i - 1][j - 1]);  // 匹配不产生删除得分，所以与「删掉」的方案取较大值
                }  // if 结束
            }  // j 循环结束
        }  // i 循环结束

        return f[m][n];  // 所有字符处理完且 pattern 全部匹配时的最大删除次数
    }  // 方法结束
};  // 类定义结束
