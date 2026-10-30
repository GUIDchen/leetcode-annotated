// 题目：945. 使数组唯一的最小增量（Minimum Increment to Make Array Unique）
// 思路：排序后贪心。维护「上一个数最终被抬到的值 y」，当前数至少要被抬到 y+1，累加它被抬升的量即可。
// 时间复杂度：O(n log n)，主要开销在排序；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minIncrementForUnique(vector<int>& nums) {  // nums 是可原地修改的整数数组，返回使元素互不相同所需的最小增量次数
        sort(nums.begin(), nums.end());  // 先升序排序，才能保证从左到右贪心时只需看前一个数
        int ans = 0, y = -1;  // ans 累计增量；y 是上一个数最终被抬到的值，-1 作为起点哨兵
        for (int x : nums) {  // 按升序依次处理每个数
            y = max(y + 1, x);  // 当前数至少要等于 y+1；若它本身更大则保持原值
            ans += y - x;  // 把 x 抬到 y 需要的增量计入答案
        }
        return ans;  // 返回最小总增量
    }
};  // 类定义结束