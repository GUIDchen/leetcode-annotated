// 题目：374. 猜数字大小（Guess Number Higher or Lower）
// 思路：答案落在 [1, n]，每次猜中点 mid，按 guess(mid) 的返回值收缩区间，缩到单点即为答案。
// 时间复杂度：O(log n)，二分收缩；空间复杂度：O(1)，只用了常数个变量。
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int guessNumber(int n) {  // n 为数字上限，返回被选中的那个数字
        int left = 1, right = n;  // 二分区间 [left, right]，初值覆盖全部候选 [1, n]
        while (left < right) {  // 区间不只剩一个元素时继续二分
            int mid = left + ((right - left) >> 1);  // 防溢出写法：先减后加，右移一位等价于除以 2
            if (guess(mid) <= 0) {  // guess 返回 0 表示猜中，返回 -1 表示答案更小，两者都说明答案在 mid 及其左侧
                right = mid;  // 答案不可能大于 mid，把右端点收到 mid（保留 mid 本身）
            } else {  // 否则猜小了，答案严格大于 mid
                left = mid + 1;  // 左端点右移到 mid + 1，排除 mid
            }
        }
        return left;  // 区间收敛到唯一候选，返回被选中的数字
    }
};  // 题解类定义结束