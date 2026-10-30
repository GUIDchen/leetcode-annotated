// 题目：2443. 反转之后的数字和（Sum of Number and Its Reverse）
// 思路：枚举加数 i ∈ [0, num]，把 i 十进制反转得到 j，判断 i + j 是否等于 num，命中即返回。
// 时间复杂度：O(num·log num)，枚举 num+1 个数、每数反转 O(log num)；空间复杂度：O(1)，只用常数个变量。
bool sumOfNumberAndReverse(int num) {  // 判断 num 能否写成「某个数 + 它的十进制反转」
    for (int i = 0; i <= num; i++) {  // 枚举较小的加数 i：两个非负整数之和为 num，故 i 不会超过 num
        int t = i;  // t 是 i 的工作副本，反转过程中会被反复除以 10
        int j = 0;  // j 累积 i 的反转结果，初值为 0
        while (t > 0) {  // 逐位剥离 t 的十进制末位，直到 t 变成 0
            j = j * 10 + t % 10;  // 把 t 的末位接到 j 的末尾（j 先整体左移一位再补末位）
            t /= 10;  // 丢掉 t 已取出的末位
        }
        if (i + j == num) {  // 检查 i 与它的反转 j 之和是否正好等于目标 num
            return 1;  // 找到一组解，返回真（C 语言中用 1 表示 true）
        }
    }
    return 0;  // 所有加数都试过仍不成立，返回假
}