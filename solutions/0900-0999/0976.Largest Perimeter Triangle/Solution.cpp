// 题目：976. 三角形的最大周长（Largest Perimeter Triangle）
// 思路：升序排序后从最长边开始往前枚举，一旦满足「两短边之和大于最长边」即为最大周长。
// 时间复杂度：O(n log n)，来自排序；空间复杂度：O(1)，只用了常数级额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestPerimeter(vector<int>& nums) {  // nums：边长数组，返回能组成的最大三角形周长
        ranges::sort(nums);  // C++20 的 ranges::sort 升序排序，最长的边在末尾
        for (int i = nums.size() - 1; i > 1; --i) {  // 从最长边开始往前枚举，i 是最长边的下标
            int c = nums[i - 1] + nums[i - 2];  // c 是另外两条较短边之和
            if (c > nums[i]) {  // 三角形判定：两短边之和严格大于最长边
                return c + nums[i];  // 命中即返回周长；从大到小枚举，第一次命中就是最大周长
            }  // if 结束
        }  // for 循环结束
        return 0;  // 没有任何三条边能组成三角形，返回 0
    }  // 题解方法结束
};  // Solution 类结束
