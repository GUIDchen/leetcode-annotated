// 题目：2009. 使数组连续的最少操作数（Minimum Number of Operations to Make Array Continuous）
// 思路：排序并去重后，枚举每个不同值作为最终连续区间的左端点，用二分求出落在 [v, v + n - 1] 里的不同元素个数 k；这些元素可以原地保留，其余 n - k 个必须修改，取最小值。
// 时间复杂度：O(n log n)，排序加每个元素一次二分；空间复杂度：O(1)，原地排序没有额外数组（不计返回值）。
class Solution {  // LeetCode 约定的题解类
public:
    int minOperations(vector<int>& nums) {  // nums 是输入数组；返回把它变成 n 个连续整数所需的最少操作次数
        sort(nums.begin(), nums.end());  // 先排序，后续才能用区间内元素个数统计「可以保留多少个」
        int m = unique(nums.begin(), nums.end()) - nums.begin();  // 用 unique 把重复元素挤到后面，m 是不同值的个数；只保证前 m 个位置互不相同
        int n = nums.size();  // n 是原数组长度，也是最终连续区间必须覆盖的整数个数
        int ans = n;  // 最坏情况是全部元素都要改，先把答案设为 n
        for (int i = 0; i < m; ++i) {  // 枚举每一个不同值作为最终连续区间的左端点
            int j = upper_bound(nums.begin() + i, nums.begin() + m, nums[i] + n - 1) - nums.begin();  // 目标区间是 [nums[i], nums[i] + n - 1]，二分找第一个大于右端点的位置 j
            ans = min(ans, n - (j - i));  // [i, j) 内的 j - i 个不同值可以原地保留，其余 n - (j - i) 个需要修改
        }  // for 循环结束
        return ans;  // 返回最少修改次数
    }  // minOperations 方法结束
};  // Solution 类结束