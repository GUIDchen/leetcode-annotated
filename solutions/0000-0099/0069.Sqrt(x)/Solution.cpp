// 题目：69. x 的平方根（Sqrt(x)）
// 思路：二分答案，在 [0, x] 中找最大的 mid 使 mid*mid <= x；用 x/mid 代替 mid*mid 避免整数溢出，区间取上中位数保证能收敛。
// 时间复杂度：O(log x)，二分区间每次折半；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mySqrt(int x) {  // x：待求平方根的非负整数
        int l = 0, r = x;  // 答案一定落在闭区间 [l, r] = [0, x] 内
        while (l < r) {  // 区间未收缩到一个点就继续二分
            int mid = (l + r + 1ll) >> 1;  // 取上中位数；先加 1 再右移一位，用 1ll 防止 l+r 溢出
            if (mid > x / mid) {  // 等价于 mid*mid > x，但写成除法不会溢出；说明 mid 太大
                r = mid - 1;  // 答案在左半区间，丢弃 mid 及其右侧
            } else {
                l = mid;  // mid*mid <= x，mid 可能是答案，把它保留在区间内继续找更大的
            }
        }
        return l;  // 区间收敛后 l 就是满足条件的最大整数，即向下取整的平方根
    }
};