// 题目：2541. 使数组中所有元素相等的最小操作数 II（Minimum Operations to Make Array Equal II）
// 思路：每次操作让一个位置 +k、另一个位置 -k，统计每个位置需要增加/减少的「k 的份数」，两边份数相等即可行。
// 时间复杂度：O(n)，一趟线性扫描；空间复杂度：O(1)，只用了两个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {  // 返回最少操作次数；k 为 0 或差值不是 k 的整数倍时返回 -1
        long long a = 0, b = 0;  // a 累计「需要增加」的份数，b 累计「需要减少」的份数；用 long long 防止累加溢出
        for (int i = 0; i < nums1.size(); ++i) {  // 逐位比较两个数组的同一位置
            int x = nums1[i], y = nums2[i];  // 取出当前位置的两个值，后面反复用到
            if (x == y) {  // 这一位已经相等，不需要任何操作
                continue;  // 跳过本位置，直接处理下一位
            }  // 结束相等判断
            if (k == 0 || (x - y) % k != 0) {  // k 为 0 时无法改变任何值；差值不是 k 的整数倍则无法用加减 k 补齐
                return -1;  // 两种情况都说明无解
            }  // 结束可解性判断
            int t = (x - y) / k;  // t 是把 nums1[i] 变成 nums2[i] 需要的「k 的份数」：正数表示要减少，负数表示要增加
            if (t < 0) {  // t 为负说明 nums1 这一位偏小，需要被增加
                a += -t;  // 把「需要增加」的份数累加到 a
            } else {  // 否则 nums1 这一位偏大，需要被减少
                b += t;  // 把「需要减少」的份数累加到 b
            }  // 结束方向判断
        }  // 结束遍历
        return a == b ? a : -1;  // 每次操作一加一减，只有两个方向份数相等才能整体配平；总操作数就是 a
    }  // 方法结束
};  // 类定义结束
