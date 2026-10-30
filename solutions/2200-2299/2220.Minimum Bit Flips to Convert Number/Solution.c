// 题目：2220. 转换数字的最少位翻转次数（Minimum Bit Flips to Convert Number）
// 思路：异或后仍为 1 的位就是两数不同的位，逐位统计 start ^ goal 中 1 的个数即可。
// 时间复杂度：O(log n)，最多检查 32 个二进制位；空间复杂度：O(1)，只用常数个变量。
int minBitFlips(int start, int goal) {  // start 与 goal 是两个整数，返回让它们相等所需的最少翻转次数
    int x = start ^ goal;  // 异或：同一位相同得 0，不同得 1，于是 x 标记了所有需要翻转的位
    int ans = 0;  // 计数器：统计 x 中 1 的个数
    while (x) {  // 只要 x 还有为 1 的位就继续统计
        ans += (x & 1);  // 取最低位，为 1 说明这一位需要翻转，计数加一
        x >>= 1;  // 右移一位，把下一位挪到最低位继续判断
    }
    return ans;  // 返回最少位翻转次数
}
