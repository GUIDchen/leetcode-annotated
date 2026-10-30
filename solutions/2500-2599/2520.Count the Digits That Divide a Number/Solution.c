// 题目：2520. 统计能整除数字的位数（Count the Digits That Divide a Number）
// 核心思路：把 num 逐位拆开，对每一位数字判断 num 能否被它整除，能整除就计数加一，最后返回计数。
// 时间复杂度：O(log num)，即 num 的位数；空间复杂度：O(1)，只用常数个变量。
int countDigits(int num) {  // num：待统计的整数；返回其中能整除 num 的位数
    int ans = 0;  // ans 统计满足条件的位数
    int cur = num;  // cur 是 num 的副本，逐位取出数字时不破坏入参
    while (cur) {  // 只要还有位没处理完就继续循环
        if (num % (cur % 10) == 0) {  // cur % 10 是当前最低位数字，判断它能否整除 num
            ans++;  // 能整除，计数加一
        }  // 结束 if
        cur /= 10;  // 去掉已处理的最低位
    }  // 结束 while
    return ans;  // 返回能整除 num 的位数
}  // 结束 countDigits