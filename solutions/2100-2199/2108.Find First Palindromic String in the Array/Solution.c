// 题目：2108. 找出数组中的第一个回文字符串（Find First Palindromic String in the Array）
// 思路：按顺序遍历每个单词，用左右双指针向中间比较判断是否回文，遇到第一个回文串立刻返回。
// 时间复杂度：O(L)，L 是所有单词字符总数（最坏情况）；空间复杂度：O(1)，只用了几个整型变量。
char* firstPalindrome(char** words, int wordsSize) {  // words 是字符串数组，wordsSize 是单词个数；返回第一个回文串（原地返回指针）
    for (int i = 0; i < wordsSize; ++i) {  // 按数组顺序逐个检查单词
        char* w = words[i];  // 取出当前单词的指针
        int len = strlen(w);  // 求当前单词长度
        bool ok = true;  // ok 标记当前单词是否回文，先假设是
        for (int j = 0, k = len - 1; j < k && ok; ++j, --k) {  // j 从左、k 从右向中间比较；一旦发现不回文就提前退出
            if (w[j] != w[k]) {  // 对应位置字符不同
                ok = false;  // 标记为不是回文
            }  // if 分支结束
        }  // 内层比较循环结束
        if (ok) {  // 整串都对称，说明是回文串
            return w;  // 直接返回这个单词（题目允许返回数组内的字符串）
        }  // if 分支结束
    }  // 外层循环结束，所有单词都不是回文
    return "";  // 返回空字符串表示没找到
}  // 函数结束