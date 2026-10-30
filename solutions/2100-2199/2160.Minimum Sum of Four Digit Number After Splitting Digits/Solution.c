// 题目：2160. 拆分数位后四位数字的最小和（Minimum Sum of Four Digit Number After Splitting Digits）
// 核心思路：把四个数位升序排序，最小的两位分别作两个数的十位、较大的两位作个位，此时两数之和最小。
// 时间复杂度：O(1)，固定只处理 4 位数位；空间复杂度：O(1)，只用长度为 4 的数组。
int cmp(const void* a, const void* b) {  // qsort 需要的比较函数
    return *(int*) a - *(int*) b;  // 转成 int 指针取值并按升序返回差值
}  // 比较函数结束

int minimumSum(int num) {  // num：输入的四位整数
    int nums[4] = {0};  // 存放拆出来的 4 个数位，顺便全部初始化为 0
    for (int i = 0; i < 4; i++) {  // 从低位到高位依次取数位
        nums[i] = num % 10;  // 取当前最低位
        num /= 10;  // 去掉这一位，准备取更高位
    }  // 取位循环结束
    qsort(nums, 4, sizeof(int), cmp);  // 把 4 个数位升序排序
    return 10 * (nums[0] + nums[1]) + nums[2] + nums[3];  // 最小的两位放十位、其余放个位，两数之和最小
}  // 函数结束