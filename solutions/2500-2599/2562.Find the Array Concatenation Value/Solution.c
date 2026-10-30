// 题目：2562. 找出数组的串联值（Find the Array Concatenation Value）
// 核心思路：双指针从两端向中间靠拢，把右值的十进制位数算出后，左值乘 10 的该次方再加右值，即完成拼接；剩余正中间的元素单独累加。
// 时间复杂度：O(n log M)，每位数字只被统计一次；空间复杂度：O(1)，只用常数个变量。
int getLen(int num) {  // 辅助函数：求十进制数的位数
    int res = 0;  // 位数计数
    while (num) {  // 反复去掉最低位，直到数字变成 0
        num /= 10;  // 整除 10，丢掉最低位
        res++;  // 位数加一
    }
    return res;  // 返回总位数
}

long long findTheArrayConcVal(int* nums, int numsSize) {  // nums：输入数组；numsSize：数组长度
    long long ans = 0;  // 串联值总和，可能超出 int，用 long long
    int i = 0;  // 左指针，指向当前最左元素
    int j = numsSize - 1;  // 右指针，指向当前最右元素
    while (i < j) {  // 左右尚未相遇时，每次拼一对
        ans += nums[i] * pow(10, getLen(nums[j])) + nums[j];  // 把 nums[j] 接到 nums[i] 后面：左值乘以 10 的「右值位数」次方再加右值
        i++;  // 左指针右移
        j--;  // 右指针左移
    }
    if (i == j) {  // 数组长度为奇数，还剩正中间一个元素没处理
        ans += nums[i];  // 中间元素直接累加
    }
    return ans;  // 返回最终串联值
}