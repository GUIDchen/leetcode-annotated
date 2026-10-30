// 题目：2278. 字母在字符串中的百分比（Percentage of Letter in String）
// 思路：用 ranges::count 统计 letter 在 s 中出现的次数，乘 100 后整除字符串长度并向下取整。
// 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int percentageLetter(string s, char letter) {  // s 为输入字符串，letter 为要统计的字母
        return 100 * ranges::count(s, letter) / s.size();  // 先乘 100 再整除，避免整数除法提前截断；结果自动向下取整
    }
};
