// 题目：3349. 检测相邻递增子数组 I（Adjacent Increasing Subarrays Detection I）
// 思路：线性扫描把数组切成极长严格递增段，用 pre/cur 记录前一段与当前段长度，候选答案只可能是 cur/2 或 min(pre, cur)。
// 时间复杂度：O(n)，数组只扫描一遍；空间复杂度：O(1)，只用了常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {  // nums：输入数组；k：要求的两段递增子数组长度
        int mx = 0, pre = 0, cur = 0;  // mx：历史最优长度；pre：前一个递增段长度；cur：当前递增段长度
        int n = nums.size();  // 缓存数组长度，避免循环条件里反复调用 size()
        for (int i = 0; i < n; ++i) {  // 从左到右线性扫描每个下标
            ++cur;  // 把 nums[i] 并入当前递增段，段长加一
            if (i == n - 1 || nums[i] >= nums[i + 1]) {  // 到达末尾，或下一元素不再更大，说明当前递增段到此结束
                mx = max({mx, cur / 2, min(pre, cur)});  // 三选一取最大：同段前后对半分 cur / 2；跨相邻两段各取一半 min(pre, cur)
                pre = cur;  // 当前段结束，成为下一轮的「前一段」
                cur = 0;  // 当前段长度清零，重新开始统计下一段
            }  // 结束当前递增段的结算
        }  // 结束主循环
        return mx >= k;  // 最大可行长度达到 k，说明存在相邻的两个长度为 k 的递增子数组
    }  // 结束题解方法
};  // 结束题解类
