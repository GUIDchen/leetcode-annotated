// 题目：3324. 出现在屏幕上的字符串序列（Find the Sequence of Strings Appeared on the Screen）
// 思路：模拟。对 target 的每个字符，以上一次得到的完整字符串为前缀，把末位字符从 'a' 一直递增到该字符，每改一次就记录一个屏幕状态。
// 时间复杂度：O(n^2)，n 为 target 长度（每个位置最多追加 26 个长度 O(n) 的字符串）；空间复杂度：O(n^2)，保存全部中间字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> stringSequence(string target) {  // target：最终要拼出的目标字符串
        vector<string> ans;  // 按时间顺序记录屏幕上出现的每一个字符串
        for (char c : target) {  // 逐个字符地把 target 构造出来
            string s = ans.empty() ? "" : ans.back();  // 上一次按键后屏幕上的完整字符串（首次为空串），作为本次的前缀
            for (char a = 'a'; a <= c; ++a) {  // 末位字符从 'a' 一直递增到目标字符 c
                string t = s + a;  // 追加当前字符得到新的屏幕内容
                ans.push_back(t);  // 每按一次键就记录一次
            }
        }
        return ans;  // 返回完整的字符串序列
    }
};
