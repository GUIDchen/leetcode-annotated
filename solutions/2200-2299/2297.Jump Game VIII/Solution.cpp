// 题目：2297. 跳跃游戏 VIII（Jump Game VIII）
// 思路：两遍单调栈求出每个位置右侧最近的不低于/严格低于它的落点并连边，再按下标递增顺序做 DP。
// 时间复杂度：O(n)，每个下标最多入栈出栈常数次；空间复杂度：O(n)，邻接表与 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minCost(vector<int>& nums, vector<int>& costs) {  // nums：各块石头的高度；costs：落到某块石头的花费；返回从 0 跳到 n-1 的最小总花费
        int n = nums.size();  // n 为石头个数
        vector<int> g[n];  // g[i] 记录从 i 一步能跳到的所有下标（邻接表）
        stack<int> stk;  // 单调栈，存放下标，从右往左扫描
        for (int i = n - 1; ~i; --i) {  // 第一遍：~i 等价于 i >= 0，从右向左遍历
            while (!stk.empty() && nums[stk.top()] < nums[i]) {  // 弹出高度严格小于 nums[i] 的下标，它们会被 i 挡住
                stk.pop();  // 这些位置不可能再成为左侧元素的最近「不低于」目标
            }
            if (!stk.empty()) {  // 栈顶就是 i 右侧最近的、高度不低于 nums[i] 的位置
                g[i].push_back(stk.top());  // 连边 i → 栈顶：满足 nums[i] <= nums[j] 且中间元素都严格小于 nums[i]
            }
            stk.push(i);  // i 入栈，留待左侧元素匹配
        }
        stk = stack<int>();  // 清空栈，准备第二遍扫描
        for (int i = n - 1; ~i; --i) {  // 第二遍：求右侧最近且高度严格低于 nums[i] 的位置
            while (!stk.empty() && nums[stk.top()] >= nums[i]) {  // 弹出高度不低于 nums[i] 的下标，它们会挡住更矮的落点
                stk.pop();  // 只保留严格更矮的候选
            }
            if (!stk.empty()) {  // 栈顶满足 nums[j] < nums[i]，且中间元素都不低于 nums[i]
                g[i].push_back(stk.top());  // 连边 i → 栈顶
            }
            stk.push(i);  // i 入栈，留待左侧元素匹配
        }
        vector<long long> f(n, 1e18);  // f[i] 表示到达第 i 块石头的最小总花费，先初始化为无穷大
        f[0] = 0;  // 起点不需要任何花费
        for (int i = 0; i < n; ++i) {  // 所有边都指向更大的下标，按 i 递增顺序即可完成 DP
            for (int j : g[i]) {  // 枚举从 i 一步可达的落点 j
                f[j] = min(f[j], f[i] + costs[j]);  // 落到 j 要支付 costs[j]，取更小的方案
            }
        }
        return f[n - 1];  // 返回到达终点的最小总花费
    }
};