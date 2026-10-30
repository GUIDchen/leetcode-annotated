// 题目：3864. 划分二进制字符串的最小费用（Minimum Cost to Partition a Binary String）
// 思路：前缀和统计任意分段的 '1' 个数，再递归分治：每个分段要么直接按规则计价，要么在长度为偶数时对半拆分，取两者较小值。
// 时间复杂度：O(n)，分治树共 O(n) 个结点、每个结点 O(1)；空间复杂度：O(n)，前缀和数组加 O(log n) 递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minCost(string s, int encCost, int flatCost) {  // s：二进制串；encCost：敏感元素单价；flatCost：全 0 分段的固定费用
        int n = s.size();  // 字符串长度
        vector<int> pre(n + 1);  // 前缀和：pre[i] 表示 s[0..i-1] 中 '1' 的个数

        for (int i = 1; i <= n; ++i) {  // 逐位构造前缀和
            pre[i] = pre[i - 1] + (s[i - 1] - '0');  // 累加当前位是否为 '1'
        }

        auto dfs = [&](this auto&& dfs, int l, int r) -> long long {  // 递归求半开区间 s[l..r) 这一段的最小费用
            int x = pre[r] - pre[l];  // 该分段中敏感元素（'1'）的个数
            long long res = x ? 1LL * (r - l) * x * encCost : flatCost;  // 不拆分时的费用：有 1 按长度×个数×单价，全 0 按 flatCost

            if ((r - l) % 2 == 0) {  // 只有长度为偶数的分段才允许对半拆分
                int m = (l + r) >> 1;  // 取中点，分成 [l, m) 与 [m, r) 两段
                res = min(res, dfs(l, m) + dfs(m, r));  // 拆分费用等于两半各自最优费用之和，与不拆分取较小者
            }

            return res;  // 返回该分段的最小费用
        };

        return dfs(0, n);  // 整串作为初始分段，答案为它的最小费用
    }
};
