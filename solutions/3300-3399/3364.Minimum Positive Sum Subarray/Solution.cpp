// 题目：3364. 最小正和子数组（Minimum Positive Sum Subarray）
// 思路：枚举左端点 i 与右端点 j，用增量 s 实时维护子数组和；当长度落在 [l, r] 且 s > 0 时更新最小答案。
// 时间复杂度：O(n^2)，需要枚举所有子数组端点；空间复杂度：O(1)，只用到常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSumSubarray(vector<int>& nums, int l, int r) {  // nums：输入数组；l、r：子数组长度允许的闭区间范围
        int n = nums.size();  // 数组长度，作为两层循环的上界
        const int inf = INT_MAX;  // INT_MAX 代表「还没有找到任何合法子数组」的无穷大
        int ans = inf;  // 答案初始化为无穷大，之后不断被更小的正和刷新
        for (int i = 0; i < n; ++i) {  // 枚举子数组的左端点 i
            int s = 0;  // 以 i 开头的子数组和，随右端点扩展而累加，避免重复求和
            for (int j = i; j < n; ++j) {  // 枚举右端点 j，此时子数组为 nums[i..j]
                s += nums[j];  // 把右端点元素并入当前子数组和，增量更新只需 O(1)
                int k = j - i + 1;  // 当前子数组长度：j - i + 1
                if (k >= l && k <= r && s > 0) {  // 长度必须落在 [l, r] 内，且和为正数，才是「正和子数组」
                    ans = min(ans, s);  // 用当前正和更新最小答案
                }  // 结束条件判断
            }  // 右端点枚举结束
        }  // 左端点枚举结束
        return ans == inf ? -1 : ans;  // 仍是 inf 说明不存在合法子数组，返回 -1；否则返回最小正和
    }  // 方法结束
};  // 类定义结束
