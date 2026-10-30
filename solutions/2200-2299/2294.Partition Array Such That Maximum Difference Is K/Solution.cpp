// 题目：2294. 划分数组使最大差为 K（Partition Array Such That Maximum Difference Is K）
// 思路：升序排序后贪心切分，当前元素与当前组最小值之差超过 k 就另起一组，这样组数最少。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序所需的递归栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int partitionArray(vector<int>& nums, int k) {  // nums：待划分的数组；k：每组内最大值与最小值之差的上限；返回所需的最少组数
        sort(nums.begin(), nums.end());  // 升序排序：最优划分中同一组的元素在排序后必然连续，可以直接贪心切分
        int ans = 1, a = nums[0];  // ans 为组数（至少 1 组）；a 记录当前组的第一个元素，也就是组内最小值
        for (int& b : nums) {  // 用引用遍历，避免元素拷贝
            if (b - a > k) {  // 当前元素与组内最小值的差超过 k，说明它不能再留在这一组
                a = b;  // 开新的一组，b 成为新组的最小值
                ++ans;  // 组数加一
            }
        }
        return ans;  // 返回最少分组数
    }
};