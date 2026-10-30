// 题目：3144. 分割字符频率相等的最少子字符串（Minimum Substring Partition of Equal Character Frequency）
// 思路：记忆化搜索，dfs(i) 表示后缀 s[i:] 的最少分段数；枚举右端点 j 时用 cnt 记字符次数、freq 记「出现次数 → 有多少个字符是这个次数」，freq 只剩一个键就说明子串内各字符频率相等。
// 时间复杂度：O(n^2)，每个状态都要枚举右端点；空间复杂度：O(n)，记忆化数组 f 与递归栈（freq 最多 26 项）。
class Solution {
public:
    int minimumSubstringsInPartition(string s) {  // s：待分割的字符串
        int n = s.size();  // n：字符串长度
        int f[n];  // f[i]：后缀 s[i:] 的最少分段数（变长数组，按 n 分配）
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示尚未计算
        auto dfs = [&](this auto&& dfs, int i) -> int {  // 自引用 lambda：this auto&& 让 lambda 能递归调用自己
            if (i >= n) {  // 已经越过末尾，没有字符需要分段
                return 0;  // 空后缀需要 0 段
            }
            if (f[i] != -1) {  // 该状态已经算过
                return f[i];  // 直接返回记忆化结果
            }
            f[i] = n - i;  // 先取上界：最坏情况每个字符单独一段，共 n - i 段
            int cnt[26]{};  // cnt[k]：字符 k 在当前子串中出现的次数
            unordered_map<int, int> freq;  // freq[c]：出现次数恰为 c 的字符种类数
            for (int j = i; j < n; ++j) {  // 枚举子串右端点 j，逐步把 s[j] 纳入统计
                int k = s[j] - 'a';  // k：字符 s[j] 的编号
                if (cnt[k]) {  // 该字符此前出现过，要先把它从旧的次数桶里移走
                    freq[cnt[k]]--;  // 旧次数桶的字符种类数减一
                    if (freq[cnt[k]] == 0) {  // 这个桶已经空了
                        freq.erase(cnt[k]);  // 删掉空桶，避免干扰下面的 freq.size() 判断
                    }
                }
                ++cnt[k];  // 该字符出现次数加一
                ++freq[cnt[k]];  // 挂到新的次数桶上
                if (freq.size() == 1) {  // 只剩一种出现次数 → 子串内各字符频率相等
                    f[i] = min(f[i], 1 + dfs(j + 1));  // 在 j 后面切一刀，递归求剩余后缀的最优分段数
                }
            }
            return f[i];  // 返回当前状态的最优解
        };
        return dfs(0);  // 从下标 0 开始，求整个字符串的最少分段数
    }
};
