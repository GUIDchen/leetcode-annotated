// 题目：462. 最小操作次数使数组元素相等 II（Minimum Moves to Equal Array Elements II）
// 思路：排序后取中位数作为目标值；所有元素到中位数的距离之和就是最小操作次数（中位数使绝对偏差和最小）。
// 时间复杂度：O(n log n)（排序）；空间复杂度：O(log n)（排序递归栈）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves2(vector<int>& nums) {  // nums 是整数数组，返回把所有元素变成同一个值所需的最小操作次数
        sort(nums.begin(), nums.end());  // 先排序，才能取到中位数作为目标值
        int k = nums[nums.size() >> 1];  // 取中位数（>> 1 即长度的一半；偶数长度取上中位数同样最优）
        int ans = 0;  // ans 累计操作次数
        for (int& v : nums) {  // 遍历每个元素（引用遍历，避免拷贝）
            ans += abs(v - k);  // 每个元素与中位数的距离就是它需要的移动步数
        }  // 结束遍历
        return ans;  // 返回总操作次数
    }  // 结束方法
};
