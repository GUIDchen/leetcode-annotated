// 题目：1523. 在区间范围内统计奇数数目（Count Odd Numbers in an Interval Range）
// 核心思路：1..x 中的奇数个数是 (x+1)/2（向下取整），用前缀差即得 [low, high] 内的奇数个数。
// 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countOdds(int low, int high) {  // low、high：闭区间的两个端点
        return (high + 1 >> 1) - (low >> 1);  // + 的优先级高于 >>，所以等价于 ((high+1)>>1) - (low>>1)，即两个前缀奇数个数相减
    }  // 方法结束
};  // 类定义结束