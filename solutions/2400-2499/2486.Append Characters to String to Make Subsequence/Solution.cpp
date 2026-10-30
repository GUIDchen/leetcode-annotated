// 题目：2486. 追加字符以获得子序列（Append Characters to String to Make Subsequence）
// 思路：双指针贪心，让 s 去匹配 t 的最长前缀，t 中没匹配上的后缀只能原样追加。
// 时间复杂度：O(|s|)，s 只扫一遍；空间复杂度：O(1)，只用两个指针。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int appendCharacters(string s, string t) {  // s：已有字符串；t：目标字符串；返回最少还需要追加的字符数
        int n = t.length(), j = 0;  // n 是 t 的长度；j 是 t 中已经匹配到的位置
        for (int i = 0; i < s.size() && j < n; ++i) {  // 扫描 s；j 到达 n 说明 t 已是子序列，可提前结束
            if (s[i] == t[j]) {  // 当前字符正好等于 t 中下一个待匹配字符
                ++j;  // 匹配成功，t 的指针后移
            }  // 不匹配就跳过 s 的这个字符
        }  // 扫描结束
        return n - j;  // t 中剩余未匹配的后缀必须原样追加到末尾
    }  // 方法结束
};  // 类定义结束