// 题目：2575. 找出字符串的可整除数组（Find the Divisibility Array of a String）
// 思路：从高位到低位逐位处理，用 (余数 × 10 + 当前数字) % m 递推，避免存储超大整数。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，用于存放返回数组。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* divisibilityArray(char* word, int m, int* returnSize) {  // word 是只含数字的字符串，m 是除数，returnSize 回传结果长度
    int n = strlen(word);  // 字符串长度，也就是结果数组的长度
    int* ans = malloc(sizeof(int) * n);  // 申请结果数组的内存，由调用方负责释放
    long long x = 0;  // x 保存当前前缀对 m 取模后的余数
    for (int i = 0; i < n; i++) {  // 从最高位开始逐位处理
        x = (x * 10 + word[i] - '0') % m;  // 在余数末尾接上当前数字，再对 m 取模
        ans[i] = x == 0 ? 1 : 0;  // 余数为 0 说明该前缀能被 m 整除
    }
    *returnSize = n;  // 告诉调用方结果数组的长度
    return ans;  // 返回结果数组
}