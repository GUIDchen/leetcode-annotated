// 题目：2522. 将字符串分割成值不超过 K 的子字符串（Partition String Into Substrings With Values at Most K）
// 核心思路：记忆化搜索。dfs(i) 表示把后缀 s[i:] 切分的最少段数；从 i 起枚举子串右端点，数值一旦超过 k 就停止，取所有可行切法的最小值再加一。
// 时间复杂度：O(n^2)，每个状态最多枚举 n 个右端点；空间复杂度：O(n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int minimumPartition(string s, int k) {  // s：只含数字的字符串；k：每个子串数值的上界
        int n = s.size();  // 字符串长度
        int f[n];  // f[i] 记忆化：后缀 s[i:] 的最少段数，0 表示尚未计算
        memset(f, 0, sizeof f);  // 初始化为 0，作为「未计算」的标记
        const int inf = 1 << 30;  // inf 表示不可达（无解），取一个足够大的哨兵值
        function<int(int)> dfs = [&](int i) -> int {  // 带记忆化的 DFS：dfs(i) 求后缀 s[i:] 的最少段数
            if (i >= n) return 0;  // 已越过末尾，无需再切分，贡献 0 段
            if (f[i]) return f[i];  // 算过就直接返回，避免重复搜索
            int res = inf;  // res 记录所有可行切法中的最小段数
            long v = 0;  // v 累积当前子串的数值，用 long 防止溢出
            for (int j = i; j < n; ++j) {  // 枚举子串右端点 j，当前子串为 s[i..j]
                v = v * 10 + (s[j] - '0');  // 把数字字符逐位拼进当前数值
                if (v > k) break;  // 数值已超过 k，更长的子串只会更大，直接跳出
                res = min(res, dfs(j + 1));  // 当前子串合法，递归求剩余后缀的段数并取最小值
            }  // 结束 for
            return f[i] = res + 1;  // 结果记入 f[i] 后返回（加 1 是算上当前这一段）
        };  // 结束 lambda
        int ans = dfs(0);  // 从下标 0 开始求解整个字符串
        return ans < inf ? ans : -1;  // 有解则返回最少段数，否则按题意返回 -1
    }  // 结束 minimumPartition
};  // 结束 Solution 类
