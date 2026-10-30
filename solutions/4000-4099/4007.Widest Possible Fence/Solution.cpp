// 题目：4007. 栅栏的最宽宽度（Widest Possible Fence）
// 思路：木板只能单块使用、两块同长拼成 2x、或两种长度拼成 x+y，所以候选宽度必为 x、2x、x+y；先按长度分组计数，再枚举基准长度 x，把每种宽度能提供的条数累加到 t，取最大值。
// 时间复杂度：O(k^2)，k 为不同长度的种数；空间复杂度：O(k)，两个哈希表分别存长度计数与宽度计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumWidth(vector<int>& planks) {  // planks：每块木板的长度；返回所有拼接方案中能得到的最大宽度
        unordered_map<int, int> cnt;  // 哈希表：木板长度 → 该长度的木板块数
        for (int x : planks) {  // 统计每种长度的木板有多少块
            cnt[x]++;  // 同长度木板计数加 1
        }  // 结束长度计数

        unordered_map<int, int> t;  // t[w]：宽度 w 最多能由多少条木板拼成
        int ans = 0;  // ans 记录所有候选中能拼出的最大条数

        for (auto& [x, v1] : cnt) {  // 枚举作为基准的一种木板长度 x 及其数量 v1
            t[x] += v1;  // 单块 x 本身就能拼成宽度 x，贡献 v1 条
            ans = max(ans, t[x]);  // 用当前结果更新答案

            t[x * 2] += v1 / 2;  // 两块长度 x 的木板首尾拼成宽度 2x，最多贡献 v1 / 2 条
            ans = max(ans, t[x * 2]);  // 更新答案

            for (auto& [y, v2] : cnt) {  // 再枚举另一种长度 y，与 x 配对成 x + y
                if (y > x) {  // 只处理 y > x，避免同一对长度被重复统计
                    t[x + y] += min(v1, v2);  // 配对条数受两种长度数量的较小值限制
                    ans = max(ans, t[x + y]);  // 更新答案
                }  // 结束配对判断
            }  // 结束长度 y 的枚举
        }  // 结束长度 x 的枚举

        return ans;  // 返回最大条数，即栅栏的最宽宽度
    }  // 结束 maximumWidth
};  // 结束 Solution 类