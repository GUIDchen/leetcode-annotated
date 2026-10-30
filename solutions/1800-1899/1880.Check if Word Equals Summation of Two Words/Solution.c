// 题目：1880. 检查某单词是否等于两单词之和（Check if Word Equals Summation of Two Words）
// 思路：把每个字母映射成数字（'a'->0、'b'->1……'j'->9），按十进制逐位拼成整数，最后判断 first + second == target。
// 时间复杂度：O(L)，L 为三个字符串的总长度；空间复杂度：O(1)，只用了常数个变量。
int f(const char* s) {  // 把字母串翻译成对应的十进制数（'a' 当 0、'b' 当 1……）
    int ans = 0;  // ans：累计翻译出的数值
    while (*s) {  // 逐字符扫描，遇到字符串结束符 '\0' 就停止
        ans = ans * 10 + (*s - 'a');  // 十进制左移一位，再加上当前字母对应的数字
        s++;  // 指针后移，处理下一个字符
    }  // 扫描结束
    return ans;  // 返回整个单词对应的数值
}  // 辅助函数结束
// 判题器会自动调用 isSumEqual，所以这个片段不需要 main 函数

bool isSumEqual(char* firstWord, char* secondWord, char* targetWord) {  // 三个单词都只含小写字母，翻译成数值后比较前两词之和与第三词
    return f(firstWord) + f(secondWord) == f(targetWord);  // 直接返回判断结果，符合题目要求
}  // isSumEqual 函数结束（判题器无需 main 函数）
