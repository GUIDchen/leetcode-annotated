// 题目：2860. 让所有学生保持开心的分组方法数（Happy Students）
// 思路：升序排序后，选前 i 个学生时，合法性等价于 nums[i-1] < i 且 nums[i] > i，枚举所有 i 计数即可。
// 复杂度：时间 O(n log n)，瓶颈是排序；空间 O(1)，只用了几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countWays(vector<int>& nums) {  // nums：每个学生的能力值
        sort(nums.begin(), nums.end());  // 升序排序，让候选分组恰好是「能力值最小的前 i 个学生」
        int ans = 0;  // 记录合法的分组方案数
        int n = nums.size();  // 学生总数
        for (int i = 0; i <= n; ++i) {  // 枚举选进组内的学生人数 i，范围 0..n（0 和 n 都合法）
            if ((i && nums[i - 1] >= i) || (i < n && nums[i] <= i)) {  // 组内有人能力值 >= i，或组外有人能力值 <= i，都不满足题意
                continue;  // 该划分不合法，直接跳过
            }
            ++ans;  // 两个条件都满足，方案数加一
        }
        return ans;  // 返回合法方案总数
    }
};