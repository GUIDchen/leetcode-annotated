// 题目：1752. 检查数组是否经排序和轮转得到（Check if Array Is Sorted and Rotated）
// 核心思路：按环形顺序比较相邻元素，统计「后者小于前者」的下降次数，排序后轮转的数组至多出现一次下降。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只使用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool check(vector<int>& nums) {  // nums：输入数组；返回是否为非降排序后轮转得到的数组
        int cnt = 0;  // 下降点计数
        for (int i = 0, n = nums.size(); i < n; ++i) {  // i 遍历每个位置，n 缓存数组长度
            cnt += nums[i] > (nums[(i + 1) % n]);  // 与下一个位置比较（取模把末尾接回开头）；条件成立相当于加 1
        }  // 循环结束
        return cnt <= 1;  // 下降点不超过 1 个才符合要求
    }  // 方法结束
};  // 题解类结束