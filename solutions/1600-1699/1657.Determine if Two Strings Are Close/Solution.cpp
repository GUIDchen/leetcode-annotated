// 题目：1657. 确定两个字符串是否接近（Determine if Two Strings Are Close）
// 思路：接近的充要条件是字符集合相同，且字符出现次数构成的多重集合相同；先比较 26 个字母是否同为 0/非 0，再排序比较频次数组。
// 时间复杂度：O(n + 26log26)；空间复杂度：O(26)，两个定长计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool closeStrings(string word1, string word2) {  // word1、word2 是待比较的两个字符串
        int cnt1[26]{};  // 第一个串的 26 个小写字母频次，值初始化
        int cnt2[26]{};  // 第二个串的频次数组
        for (char& c : word1) {  // 统计 word1 的字符频次
            ++cnt1[c - 'a'];  // 映射到 0..25 的下标后计数
        }  // 循环结束
        for (char& c : word2) {  // 统计 word2 的字符频次
            ++cnt2[c - 'a'];  // 映射到 0..25 的下标后计数
        }  // 循环结束
        for (int i = 0; i < 26; ++i) {  // 逐个字母检查两个串的字符集合是否一致
            if ((cnt1[i] == 0) != (cnt2[i] == 0)) {  // 一个串有该字母而另一个没有，就不可能接近
                return false;  // 直接返回 false
            }  // 判断结束
        }  // 集合检查结束
        sort(cnt1, cnt1 + 26);  // 排序后忽略字母身份，只比较频次的多重集合
        sort(cnt2, cnt2 + 26);  // 第二个频次数组同样排序
        return equal(cnt1, cnt1 + 26, cnt2);  // 排序后逐位相等即说明两个串接近
    }  // 方法结束
};  // Solution 类定义结束