// 题目：2535. 数组元素和与数字和的绝对差（Difference Between Element Sum and Digit Sum of an Array）
// 思路：一趟遍历同时累加元素和 x 与各元素的十进制数位和 y，最后返回 x - y（该差恒非负）。
// 时间复杂度：O(n log M)，M 为元素最大值，拆位代价为位数；空间复杂度：O(1)，只用常数个变量。
int differenceOfSum(int* nums, int numsSize) {  // nums 为数组，numsSize 为长度；返回元素和与数字和之差
    int x = 0, y = 0;  // x 累加元素和，y 累加所有元素的数位和
    for (int i = 0; i < numsSize; i++) {  // 逐个处理数组元素
        int v = nums[i];  // 取当前元素；用副本 v，因为下一步要把 v 反复除以 10 拆位
        x += v;  // 把当前元素累加进元素和
        while (v > 0) {  // 只要 v 还有数位就继续拆
            y += v % 10;  // 取最低位累加到数位和
            v /= 10;  // 去掉最低位，为取下一高位做准备
        }  // 拆位循环结束
    }  // 遍历结束
    return x - y;  // 元素和减数位和即为答案，题目保证结果非负
}  // 函数结束
