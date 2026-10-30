// 题目：2264. 字符串中最大的 3 位相同数字（Largest 3-Same-Digit Number in String）
// 思路：从 '9' 到 '0' 降序枚举数字，构造三位相同字符组成的串，用 find 判断它是否作为子串出现，首次命中即为最大的答案。
// 时间复杂度：O(10 * n) = O(n)，n 为字符串长度（每次 find 为 O(n)，最多 10 次）；空间复杂度：O(1)，只用了长度为 3 的临时字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string largestGoodInteger(string num) {  // num：由数字字符组成的字符串
        for (char i = '9'; i >= '0'; --i) {  // 从 '9' 递减到 '0'，保证先枚举到的一定是字典序最大的数字
            string s(3, i);  // 构造由 3 个相同字符 i 组成的候选子串
            if (num.find(s) != string::npos) {  // 若该候选子串在 num 中出现过
                return s;  // 因为降序枚举，第一次命中就是最大值，立即返回
            }
        }
        return "";  // 所有数字都没有连续出现三次，按题意返回空串
    }
};