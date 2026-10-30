// 3760. 不同首字母的子字符串数目（Maximum Substrings With Distinct Start）
// 核心思路：每个不同的字符都能作为某个子串的首字母，因此最多可选的不同首字母子串数就等于字符串中不同字符的种数。
// 复杂度：时间 O(n)，空间 O(1)（固定 26 个桶）。
class Solution {  // 定义解法类
public:  // 公有接口
    int maxDistinct(string s) {  // 接口：返回首字母互不相同的子串最大数量
        int ans = 0;  // ans 统计出现过的不同字母种数
        int cnt[26]{};  // cnt 记录每个字母出现的次数，初始全为零
        for (char c : s) {  // 遍历字符串中的每个字符
            if (++cnt[c - 'a'] == 1) {  // 该字母计数加一，若恰好等于 1 说明是第一次出现
                ++ans;  // 首次出现即贡献一种新的首字母
            }  // if 结束
        }  // for 结束
        return ans;  // 不同字母种数就是答案
    }  // 方法结束
};  // 类定义结束
