// 题目：5. 最长回文子串（Longest Palindromic Substring）
// 思路：区间 DP，f[i][j] 表示 s[i..j] 是否为回文；按区间长度从小到大转移 f[i][j] = (s[i]==s[j]) && f[i+1][j-1]。
// 时间复杂度：O(n^2)，枚举全部 O(n^2) 个区间；空间复杂度：O(n^2)，二维布尔表。
char* longestPalindrome(char* s) {  // s 为输入字符串，返回最长回文子串（堆上分配，调用方负责释放）
    int n = strlen(s);  // 字符串长度
    bool** f = (bool**) malloc(n * sizeof(bool*));  // 申请 n 行的二维布尔表：f[i][j] 表示 s[i..j] 是否回文
    for (int i = 0; i < n; ++i) {  // 逐行申请内存
        f[i] = (bool*) malloc(n * sizeof(bool));  // 第 i 行放 n 个 bool
        for (int j = 0; j < n; ++j) {  // 遍历这一行的每一列
            f[i][j] = true;  // 全部初始化为 true：长度 1、2 的区间靠这个初值直接成立
        }
    }
    int k = 0, mx = 1;  // k 记录最长回文子串的起点，mx 记录其长度（单个字符至少是回文，长度 1）
    for (int i = n - 2; ~i; --i) {  // i 从 n-2 倒着走（~i 等价于 i != -1），保证 f[i+1][j-1] 已经算好
        for (int j = i + 1; j < n; ++j) {  // 只枚举长度不小于 2 的区间
            f[i][j] = false;  // 先假设该区间不是回文
            if (s[i] == s[j]) {  // 首尾字符相同，才有可能构成回文
                f[i][j] = f[i + 1][j - 1];  // 是否回文取决于去掉首尾后的内部区间
                if (f[i][j] && mx < j - i + 1) {  // 确认是回文，且长度超过当前最优
                    mx = j - i + 1;  // 更新最长长度
                    k = i;  // 更新最长子串的起点
                }
            }
        }
    }
    char* res = (char*) malloc((mx + 1) * sizeof(char));  // 为答案申请 mx+1 个字节，多出的一字节放结束符
    strncpy(res, s + k, mx);  // 把 s[k..k+mx-1] 复制到结果缓冲区
    res[mx] = '\0';  // strncpy 不会自动补 '\0'，这里手动补上
    for (int i = 0; i < n; ++i) {  // 释放二维表的每一行
        free(f[i]);  // 释放第 i 行
    }
    free(f);  // 释放行指针数组
    return res;  // 返回最长回文子串
}
