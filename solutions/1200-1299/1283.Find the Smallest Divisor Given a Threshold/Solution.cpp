// 题目：1283. 使结果不超过阈值的最小除数（Find the Smallest Divisor Given a Threshold）
// 思路：答案具有单调性——除数越大，除后取整之和越小，因此可以二分除数，找最小的可行值。
// 时间复杂度：O(n·log max(nums))，每轮二分扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestDivisor(vector<int>& nums, int threshold) {  // 返回使「各元素除以它向上取整之和」不超过 threshold 的最小除数
        int l = 1;  // 二分下界：除数至少为 1
        int r = *max_element(nums.begin(), nums.end());  // 二分上界：取最大值，此时和恰为元素个数
        while (l < r) {  // 二分查找最小的可行除数
            int mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2
            int s = 0;  // 记录当前除数下向上取整之和
            for (int x : nums) {  // 遍历每个元素累加
                s += (x + mid - 1) / mid;  // 整数除法实现向上取整 ceil(x / mid)
            }
            if (s <= threshold) {  // 当前除数可行，答案不会更大
                r = mid;  // 保留 mid 并收缩右边界
            } else {  // 当前除数太小导致和超阈值
                l = mid + 1;  // 除数必须更大，收缩左边界
            }
        }
        return l;  // 循环结束时 l == r，即最小的可行除数
    }
};  // 题解类定义结束（本文件末尾无换行，已保留）