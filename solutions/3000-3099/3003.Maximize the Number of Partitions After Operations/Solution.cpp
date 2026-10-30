// 题目：3003. 执行操作后的最大分割数量（Maximize the Number of Partitions After Operations）
// 思路：记忆化 DFS + 26 位掩码。cur 是当前段出现过的字母集合，t 表示还有没有一次改字母的机会；从左到右尽量延长当前段，超限就切段。
// 时间复杂度：记忆化后为 O(访问到的状态数)，最坏 O(n × 2^26)；空间复杂度：O(访问到的状态数)，哈希表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxPartitionsAfterOperations(string s, int k) {  // s：输入字符串；k：每个分段允许包含的不同字母数上限；返回划分出的最大段数
        int n = s.size();  // 字符串长度
        unordered_map<long long, int> f;  // 记忆化表：键由 (i, cur, t) 打包而成，值是该状态能得到的最大段数
        auto dfs = [&](this auto&& dfs, int i, int cur, int t) -> int {  // 递归 lambda：i 为当前下标，cur 为当前段的字母掩码，t 表示是否还能修改一次字母
            if (i >= n) {  // 已经走到字符串末尾
                return 1;  // 最后一段也要计入段数
            }
            long long key = (long long) i << 32 | cur << 1 | t;  // 把三个参数压进一个 64 位整数，作为缓存键
            if (f.count(key)) {  // 该状态已经计算过
                return f[key];  // 直接返回缓存值
            }
            int v = 1 << (s[i] - 'a');  // 当前字符对应的比特位
            int nxt = cur | v;  // 把当前字符并入当前段的字母集合
            int ans = __builtin_popcount(nxt) > k ? dfs(i + 1, v, t) + 1 : dfs(i + 1, nxt, t);  // 不修改时：字母种类超过 k 就必须在此切段（新段只含当前字符、段数加一），否则继续延长当前段
            if (t) {  // 还有修改机会，枚举把 s[i] 换成哪个字母
                for (int j = 0; j < 26; ++j) {  // 逐个尝试 26 个字母
                    nxt = cur | (1 << j);  // 替换后当前段的字母集合
                    if (__builtin_popcount(nxt) > k) {  // 替换后字母种类超过 k，被迫切段
                        ans = max(ans, dfs(i + 1, 1 << j, 0) + 1);  // 用掉修改机会，新段只含替换后的字母，段数加一
                    } else {  // 否则替换后仍在 k 种以内
                        ans = max(ans, dfs(i + 1, nxt, 0));  // 用掉修改机会，继续延长当前段，不增加段数
                    }
                }
            }
            return f[key] = ans;  // 把该状态的最优解写入缓存并返回
        };  // 递归 lambda 定义结束
        return dfs(0, 0, 1);  // 从下标 0、空掩码、还有一次修改机会开始搜索
    }
};
