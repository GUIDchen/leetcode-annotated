// 题目：3034. 匹配模式数组的子数组数目 I（Number of Subarrays That Match a Pattern I）
// 思路：把相邻元素的大小关系压缩成 1/0/-1，再以每个位置为起点，暴力比对长度 m 的关系序列是否与 pattern 完全一致。
// 时间复杂度：O(n·m)，共 n-m 个起点、每个起点最多比对 m 次；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {  // nums：原数组；pattern：待匹配的关系模式
        int n = nums.size(), m = pattern.size();  // n 为数组长度，m 为模式长度（也等于子数组长度减一）
        int ans = 0;  // 累计满足条件的子数组个数
        auto f = [](int a, int b) {  // 小工具函数：把相邻两个元素的大小关系标准化
            return a == b ? 0 : (a < b ? 1 : -1);  // 相等记 0，后者更大记 1，否则记 -1
        };
        for (int i = 0; i < n - m; ++i) {  // 枚举子数组左端点；子数组长度是 m+1，所以上界是 n-m（开区间）
            int ok = 1;  // 标记当前子数组是否整体匹配，先假定匹配
            for (int k = 0; k < m && ok == 1; ++k) {  // 逐位比对 m 个相邻关系，一旦失配就提前退出
                if (f(nums[i + k], nums[i + k + 1]) != pattern[k]) {  // 第 k 对相邻元素的关系与 pattern[k] 不同
                    ok = 0;  // 标记为不匹配
                }
            }
            ans += ok;  // ok 为 1 说明整段都匹配，计数加一；为 0 则加零
        }
        return ans;  // 返回匹配的子数组总数
    }
};