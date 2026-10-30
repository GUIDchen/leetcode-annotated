// 题目：367. 有效的完全平方数（Valid Perfect Square）
// 思路：在 [1, num] 上二分最小的 x 使 x*x >= num，最后判断 x*x 是否恰好等于 num。
// 时间复杂度：O(log num)，二分次数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPerfectSquare(int num) {  // num：待判断的正整数
        int l = 1, r = num;  // 二分区间取 [1, num]（num >= 1 时平方根不会超过 num）
        while (l < r) {  // 区间未收敛时继续二分
            int mid = l + (r - l) / 2;  // 用 l + (r - l) / 2 求中点，避免 l + r 溢出
            if (1LL * mid * mid >= num) {  // 1LL 先把 mid 提升为 long long，防止 mid * mid 溢出 int
                r = mid;  // 中点平方过大，答案在左半区（含 mid）
            } else {  // mid 平方不足，答案在右半区，故排除 mid
                l = mid + 1;  // 收紧右边界到 mid
            }  // 右边界左移后的闭合
        }  // 左边界右移一位
        return 1LL * l * l == num;  // 循环收敛到唯一候选 l
    }  // 最终校验 l*l 是否恰好等于 num（同样用 1LL 防溢出）
};  // 方法结束