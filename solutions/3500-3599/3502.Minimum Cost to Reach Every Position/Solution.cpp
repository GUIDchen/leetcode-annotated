// 题目：3502. 到达每个位置的最小费用（Minimum Cost to Reach Every Position）
// 思路：到达位置 i 要么直接付费与 i 交换，要么先付费与某个 j < i 交换再免费向前换位，故答案就是 cost 的前缀最小值。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，除答案数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minCosts(vector<int>& cost) {  // cost：与每个位置的人换位所需费用，返回到达每个位置的最小总费用
        int n = cost.size();  // 位置个数
        vector<int> ans(n);  // 结果数组，ans[i] 表示到达位置 i 的最小费用
        int mi = cost[0];  // 到达位置 0 只能付 cost[0]，先把它作为前缀最小值
        for (int i = 0; i < n; ++i) {  // 从左到右扫描每个位置
            mi = min(mi, cost[i]);  // 维护前缀最小值：付更便宜的前一个位置，再免费向前走
            ans[i] = mi;  // 到达位置 i 的最小费用就是这个前缀最小值
        }  // 循环结束
        return ans;  // 返回每个位置的最小费用
    }  // 方法结束
};  // 类定义结束