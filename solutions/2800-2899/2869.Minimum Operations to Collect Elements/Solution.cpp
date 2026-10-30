// 题目：2869. 收集元素的最少操作次数（Minimum Operations to Collect Elements）
// 思路：从数组尾部倒序扫描，用布尔数组标记 1..k 中已被收集的数，集齐 k 个时立刻返回已取走的元素个数。
// 时间复杂度：O(n)，最坏倒序扫完整个数组；空间复杂度：O(n)，标记数组与输入等长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int k) {  // nums 是输入数组，k 表示要收齐 1..k 这 k 个数
        int n = nums.size();  // 记录数组长度，后面把下标换算成操作次数要用
        vector<bool> isAdded(n);  // 标记数组：isAdded[x-1] 为真表示数值 x 已经被收集
        int count = 0;  // 已收集到的不同数值个数
        for (int i = n - 1;; --i) {  // 从末尾倒序扫描：每次操作取走的正是当前最后一个元素
            if (nums[i] > k || isAdded[nums[i] - 1]) {  // 大于 k 的数用不上，重复出现的数也不该重复计数
                continue;  // 直接跳过，不算一次有效收集
            }  // 无效元素过滤结束
            isAdded[nums[i] - 1] = true;  // 把数值 nums[i] 标记为已收集
            if (++count == k) {  // 先自增再与 k 比较：集齐 1..k 时立刻可以结束
                return n - i;  // 从下标 n-1 扫到 i，一共取了 n-i 次操作
            }  // 收集完成判断结束
        }  // 循环体结束（题目保证有解，所以一定会 return）
    }  // 方法结束
};  // 类定义结束