// 题目：1880. 检查某单词是否等于两单词之和（Check if Word Equals Summation of Two Words）
// 思路：把每个字母映射成数字（'a'->0、'b'->1……'j'->9），按十进制逐位拼成整数，最后判断 first + second == target。
// 时间复杂度：O(L)，L 为三个字符串的总长度；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {  // firstWord、secondWord、targetWord：三个只含小写字母的单词
        auto f = [](string& s) -> int {  // 局部 lambda：把字母串翻译成对应的十进制数（'a' 当 0）
            int ans = 0;  // ans：累计翻译出的数值
            for (char c : s) {  // 按值逐个取出字符
                ans = ans * 10 + (c - 'a');  // 十进制左移一位，再加上当前字母对应的数字
            }  // 单词遍历结束
            return ans;  // 返回整个单词对应的数值
        };  // lambda 定义结束
        return f(firstWord) + f(secondWord) == f(targetWord);  // 直接比较前两词之和与目标词
    }  // 方法结束
};  // 类定义结束
