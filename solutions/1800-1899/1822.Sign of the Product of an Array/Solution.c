// 题目：1822. 数组元素积的符号（Sign of the Product of an Array）
// 核心思路：不真的求乘积（必然溢出），只统计负号个数：一旦遇到 0 结果就是 0，每遇到一个负数就把符号翻转一次。
// 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，仅用常数个变量。
int arraySign(int* nums, int numsSize) {  // nums 是输入数组，numsSize 是数组长度（C 判题片段，可能没有 main）
    int ans = 1;  // ans 只记录符号，取值 1（正）或 -1（负）
    for (int i = 0; i < numsSize; i++) {  // 遍历数组中的每一个元素
        if (nums[i] == 0) {  // 只要出现 0，整个乘积必然是 0
            return 0;  // 提前返回 0，无需继续统计
        }
        if (nums[i] < 0) {  // 每遇到一个负数，符号翻转一次
            ans *= -1;  // 乘 -1 等价于翻转正负号
        }
    }
    return ans;  // 没有出现 0，返回统计出的最终符号
}  // 函数结束