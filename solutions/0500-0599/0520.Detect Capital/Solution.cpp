// 题目：520. 检测大写字母（Detect Capital）
// 思路：统计大写字母个数 cnt，全部合法情形只有三种：全小写、全大写、仅首字母大写。
// 时间复杂度：O(n)，只需遍历一次字符串；空间复杂度：O(1)，只用一个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公有方法区
    bool detectCapitalUse(string word) {  // word：待判定的字符串；返回它的大小写用法是否合法
        int cnt = count_if(word.begin(), word.end(), [](char c) { return isupper(c); });  // count_if 遍历整个字符串，lambda 判断每个字符是否大写，得到大写字母个数 cnt
        return cnt == 0 || cnt == word.length() || (cnt == 1 && isupper(word[0]));  // 返回判定：没有大写（全小写）/ 全部大写 / 恰好一个大写且它在首位（仅首字母大写）
    }  // 方法结束
};  // 类定义结束