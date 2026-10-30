// 3456. 找出长度为 K 的特殊子字符串 / Find Special Substring of Length K
// 核心思路：按连续相同字符切分成若干段，只要存在一段的长度恰好等于 k，就说明存在长度为 k 的特殊子字符串。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 公有接口
    bool hasSpecialSubstring(string s, int k) {  // 判断 s 中是否存在长度为 k 的特殊子字符串
        int n = s.length();  // 字符串长度
        for (int l = 0, cnt = 0; l < n;) {  // l 为每一段连续相同字符的起点
            int r = l + 1;  // r 从 l 的下一位开始扩展
            while (r < n && s[r] == s[l]) {  // 向右扩展，直到字符改变或越界
                ++r;  // 继续右移
            }  // 结束扩展
            if (r - l == k) {  // 该段长度恰好为 k，即为所求
                return true;  // 直接返回存在
            }  // 结束长度判断
            l = r;  // 跳到下一段的起点
        }  // 结束分段遍历
        return false;  // 所有段都不满足，返回不存在
    }  // 结束 hasSpecialSubstring
};  // 结束题解类
