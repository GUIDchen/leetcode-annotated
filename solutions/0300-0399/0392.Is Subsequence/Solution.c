// 题目：392. 判断子序列（Is Subsequence）
// 思路：双指针，i 扫 s、j 扫 t，字符相同时 i 前进，j 始终前进，最后看 i 是否走完 s。
// 时间复杂度：O(m + n)，两个串各扫一遍；空间复杂度：O(1)，只用了两个指针。
bool isSubsequence(char* s, char* t) {  // s 是待判断的子序列，t 是原字符串，返回 s 是否为 t 的子序列
    int m = strlen(s);  // 取 s 的长度 m，作为 i 是否走完的判断值
    int n = strlen(t);  // 取 t 的长度 n，作为 j 的上界
    int i = 0;  // i 是 s 中已匹配到的位置，只有匹配成功才前进
    for (int j = 0; i < m && j < n; ++j) {  // j 在 t 上单调前进；i 走完或 j 越界就结束
        if (s[i] == t[j]) {  // 当前两个字符相同，匹配成功
            ++i;  // s 的指针前进一位，表示该字符已在 t 中按序找到
        }
    }
    return i == m;  // i 走到 m 说明 s 的字符都按顺序在 t 中出现过
}