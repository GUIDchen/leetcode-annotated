// 题目：2469. 温度转换（Convert the Temperature）
// 核心思路：直接套换算公式，开尔文 = 摄氏度 + 273.15，华氏度 = 摄氏度 × 1.8 + 32，把两个结果依次放进 malloc 出来的数组返回。
// 时间复杂度：O(1)，只有常数次运算；空间复杂度：O(1)，返回数组固定两个 double。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* convertTemperature(double celsius, int* returnSize) {  // celsius 是摄氏温度，returnSize 输出返回数组的长度
    double* ans = malloc(sizeof(double) * 2);  // 返回数组由调用方 free，所以要用 malloc 分配两个 double
    ans[0] = celsius + 273.15;  // 摄氏度转开尔文：加 273.15
    ans[1] = celsius * 1.8 + 32;  // 摄氏度转华氏度：乘 1.8 再加 32
    *returnSize = 2;  // 告诉判题器返回数组有两个元素
    return ans;  // 返回结果数组的首地址
}