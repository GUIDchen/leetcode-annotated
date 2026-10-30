// 题目：1957. 删除字符使字符串变好（Delete Characters to Make Fancy String）
// 思路：从左到右贪心保留字符，只要当前字符不会让末尾出现三个连续相同字符就追加到答案里。
// 时间复杂度：O(n)，扫描字符串一次；空间复杂度：O(n)，答案字符串最多与原串等长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string makeFancyString(string s) {  // s 为原字符串，返回删除若干字符后的「好字符串」（无三连相同字符）
        string ans = "";  // 结果串，逐个拼接被保留下来的字符
        for (int i = 0; i < s.length(); ++i) {  // 逐字符扫描原串
            char c = s[i];  // 取出当前字符，方便与前面两个字符比较
            if (i < 2 || c != s[i - 1] || c != s[i - 2]) {  // 前两个字符无条件保留；其余字符必须与前两个都不同，才不会形成三连
                ans += c;  // 该字符安全，追加到答案末尾
            }
        }
        return ans;  // 返回构造好的好字符串
    }
};
