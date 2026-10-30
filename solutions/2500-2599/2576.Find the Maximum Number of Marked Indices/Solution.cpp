// 题目：2576. 求出最多标记下标（Find the Maximum Number of Marked Indices）
// 思路：排序后把数组分成左右两半，用双指针贪心匹配，让右半的每个元素尽量去配对左半的最小可用元素。
// 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，只用到常数个下标变量（不计排序开销）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNumOfMarkedIndices(vector<int>& nums) {  // nums：输入数组，返回最多能标记的下标个数
        ranges::sort(nums);  // C++20 的 ranges::sort，把数组按升序排列
        int i = 0, n = nums.size();  // i 指向左半部分下一个待配对的位置；n 是数组长度
        for (int j = (n + 1) / 2; j < n; ++j) {  // 右半部分从中间开始扫描，保证同一个下标不会被重复使用
            if (nums[i] * 2 <= nums[j]) {  // 右半元素至少是左半元素的两倍，满足题目配对条件
                ++i;  // 配对成功，左指针后移，等待下一个较小的元素
            }
        }
        return i * 2;  // 每成功配对一组贡献两个下标，因此返回配对数的两倍
    }
};
