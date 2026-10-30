// 题目：3350. 检测相邻递增子数组 II（Adjacent Increasing Subarrays Detection II）
// 思路：极长递增段划分后，最大合法长度只能来自段内前后对半分 cur/2 或相邻两段取小 min(pre, cur)，取全局最大即可。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxIncreasingSubarrays(vector<int>& nums) {  // nums：输入数组
        int ans = 0, pre = 0, cur = 0;  // ans：历史最优长度；pre：前一个递增段长度；cur：当前递增段长度
        int n = nums.size();  // 缓存数组长度，避免循环条件里反复调用 size()
        for (int i = 0; i < n; ++i) {  // 从左到右线性扫描每个下标
            ++cur;  // 把 nums[i] 并入当前递增段，段长加一
            if (i == n - 1 || nums[i] >= nums[i + 1]) {  // 到达末尾，或下一元素不再更大，说明当前递增段到此结束
                ans = max({ans, cur / 2, min(pre, cur)});  // 三选一取最大：同段前后对半分 cur / 2；跨相邻两段各取一半 min(pre, cur)
                pre = cur;  // 当前段结束，成为下一轮的「前一段」
                cur = 0;  // 当前段长度清零，重新开始统计下一段
            }  // 结束当前递增段的结算
        }  // 结束主循环
        return ans;  // 返回全局最大的合法子数组长度
    }  // 结束题解方法
};  // 结束题解类
