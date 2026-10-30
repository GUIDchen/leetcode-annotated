// 题目：2565. 最少得分子序列（Subsequence With the Minimum Score）
// 思路：先正/反向贪心预处理出 t 每个位置在 s 中最早、最晚能匹配的下标；再二分「被删除的那段 t 的长度 len」，用预处理结果在 O(n) 内判断是否存在可行的删除区间。
// 时间复杂度：O((m + n) log n)，m、n 分别为 s、t 的长度；空间复杂度：O(n)，两个长度为 n 的辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumScore(string s, string t) {  // s 是长串，t 要删掉最少字符后才成为 s 的子序列
        int m = s.size(), n = t.size();  // m：s 的长度；n：t 的长度
        vector<int> f(n, 1e6);  // f[j]：正向扫描时 t[j] 最早能匹配到 s 的下标（匹配不到就保留大值 1e6）
        vector<int> g(n, -1);  // g[j]：反向扫描时 t[j] 最晚能匹配到 s 的下标（匹配不到就是 -1）
        for (int i = 0, j = 0; i < m && j < n; ++i) {  // 正向双指针：i 扫 s，j 扫 t
            if (s[i] == t[j]) {  // 字符相同，说明 t[j] 可以落在 s 的位置 i 上
                f[j] = i;  // 记录 t[j] 最早的匹配位置
                ++j;  // t 前进一位，因为子序列必须保持相对顺序
            }
        }
        for (int i = m - 1, j = n - 1; i >= 0 && j >= 0; --i) {  // 反向双指针：从两个串的末尾往前匹配
            if (s[i] == t[j]) {  // 从后往前遇到相同字符
                g[j] = i;  // 记录 t[j] 最晚的匹配位置
                --j;  // t 向左移动一位
            }
        }

        auto check = [&](int len) {  // 判断：是否存在长度为 len 的 t 子串，删掉它之后「剩余前缀 + 剩余后缀」仍是 s 的子序列
            for (int k = 0; k < n; ++k) {  // 枚举被删子串的起点 k，即删除 t[k .. k+len-1]
                int i = k - 1, j = k + len;  // i：左侧被保留前缀的末位下标；j：右侧被保留后缀的首位下标
                int l = i >= 0 ? f[i] : -1;  // 左前缀末位在 s 中最早的匹配下标；前缀为空时取 -1，视作位于 s 开头之前
                int r = j < n ? g[j] : m + 1;  // 右后缀首位在 s 中最晚的匹配下标；后缀为空时取 m+1，视作位于 s 末尾之后
                if (l < r) {  // 左侧匹配位置严格早于右侧，说明前后缀能同时嵌入 s 且中间留有空隙
                    return true;  // 该长度可行，立即返回
                }
            }
            return false;  // 所有起点都不可行，说明 len 还不够大
        };

        int l = 0, r = n;  // 二分删除长度的区间 [l, r]；删掉整个 t（n 个字符）一定可行
        while (l < r) {  // 经典二分：寻找最小的可行长度
            int mid = (l + r) >> 1;  // 取中点，试删除长度 mid
            if (check(mid)) {  // mid 长度可行
                r = mid;  // 答案不会超过 mid，收缩右边界
            } else {  // mid 长度不可行
                l = mid + 1;  // 答案必然更大，收缩左边界
            }
        }
        return l;  // 二分收敛到最小可行删除长度，就是「最少得分」
    }
};