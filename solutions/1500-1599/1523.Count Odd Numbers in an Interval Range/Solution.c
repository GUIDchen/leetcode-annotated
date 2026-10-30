// 题目：1523. 在区间范围内统计奇数数目（Count Odd Numbers in an Interval Range）
// 核心思路：1..x 中的奇数个数是 (x+1)/2（向下取整），用前缀差即得区间 [low, high] 内的奇数个数。
// 时间复杂度：O(1)；空间复杂度：O(1)。
int countOdds(int low, int high) {  // low、high：闭区间的两个端点，返回其中奇数的个数
    return ((high + 1) >> 1) - (low >> 1);  // >>1 就是除以 2 向下取整：(high+1)>>1 是 1..high 的奇数个数，(low>>1) 是 1..low-1 的奇数个数，相减即区间内奇数个数
}  // 函数体结束（C 判题片段，没有 main）