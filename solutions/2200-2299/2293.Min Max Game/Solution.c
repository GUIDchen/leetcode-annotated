// 题目：2293. 极大极小游戏（Min Max Game）
// 核心思路：原地模拟。每轮长度减半，偶数下标取相邻两数的较小值、奇数下标取较大值，结果写回数组前部，缩到 1 个元素即答案。
// 时间复杂度：O(n)，总操作数 n + n/2 + ... < 2n；空间复杂度：O(1)，只用了常数个临时变量。
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 取较小值的宏，用宏避免函数调用开销
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 取较大值的宏，与 min 对称

int minMaxGame(int* nums, int numsSize) {  // nums：输入数组；numsSize：元素个数；返回游戏结束后剩下的那个数
    while (numsSize != 1) {  // 长度还没缩到 1，继续下一轮
        numsSize >>= 1;  // 每轮长度减半，新长度是旧长度的一半
        for (int i = 0; i < numsSize; i++) {  // 只遍历前 numsSize 个位置，结果就地覆盖旧数据，无需额外数组
            int a = nums[i << 1];  // 左子元素：下标 2i，用左移一位实现乘 2
            int b = nums[i << 1 | 1];  // 右子元素：下标 2i+1，先移位再按位或 1
            nums[i] = i & 1 ? max(a, b) : min(a, b);  // 奇数下标取较大值、偶数下标取较小值，把本轮结果写回数组前部
        }  // 结束本轮合并
    }  // 结束 while，长度已缩到 1
    return nums[0];  // 只剩一个元素时它就是答案
}  // 结束 minMaxGame 函数