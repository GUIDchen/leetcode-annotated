// 题目：2351. 第一个出现两次的字母（First Letter to Appear Twice）
// 思路：长度 26 的计数数组边扫描边累加，某个字母的计数达到 2 时立刻返回该字母。
// 时间复杂度：O(n)，一次遍历即可；空间复杂度：O(1)，数组大小固定为 26。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char repeatedCharacter(string s) {  // s：只含小写字母的字符串
        int cnt[26]{};  // 每个字母的出现次数，值初始化为 0
        for (int i = 0;; ++i) {  // 题目保证有解，循环上界可以省略
            if (++cnt[s[i] - 'a'] == 2) {  // 先把当前字母的计数加一，再判断是否恰好达到 2 次
                return s[i];  // 达到 2 次，当前字母即为答案
            }
        }
    }
};