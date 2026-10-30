// 题目：1234. 替换子串得到平衡字符串（Replace the Substring for Balanced String）
// 思路：先统计整串各字符数量，再用滑动窗口把「窗口内字符」当作待替换部分，只要窗口外每种字符都不超过 n/4 即可收缩窗口求最短。
// 时间复杂度：O(n)，双指针各移动一次；空间复杂度：O(1)，只用了长度为 4 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int balancedString(string s) {  // s 只含 Q/W/E/R，返回使它平衡所需替换的最短子串长度
        int cnt[4]{};  // 四种字符的计数器，{} 保证初始化为 0
        string t = "QWER";  // 固定顺序的字符表，把字符映射到 0..3 的下标
        int n = s.size();  // 字符串长度
        for (char& c : s) {  // 遍历整串统计每种字符出现的次数
            cnt[t.find(c)]++;  // t.find(c) 把字符换成 0..3 的下标，再累加计数
        }  // for 结束
        int m = n / 4;  // 平衡时每种字符应有的个数
        if (cnt[0] == m && cnt[1] == m && cnt[2] == m && cnt[3] == m) {  // 四种字符都已经等于 m，原串本身平衡
            return 0;  // 不需要任何替换
        }  // if 结束
        int ans = n;  // 答案上界：最坏情况需要替换整个字符串
        for (int i = 0, j = 0; i < n; ++i) {  // 滑动窗口：i 是右端点，j 是左端点（都在从左往右移动）
            cnt[t.find(s[i])]--;  // 把 s[i] 划入待替换窗口，窗口外该字符的计数减一
            while (j <= i && cnt[0] <= m && cnt[1] <= m && cnt[2] <= m && cnt[3] <= m) {  // 窗口外四种字符都不超过 m，说明替换这个窗口就能平衡
                ans = min(ans, i - j + 1);  // 用当前窗口长度更新答案
                cnt[t.find(s[j++])]++;  // 左端点右移：s[j] 回到窗口外，计数加一（j++ 在此完成自增）
            }  // while 结束
        }  // for 结束
        return ans;  // 返回最短需要替换的子串长度
    }  // 方法结束
};  // 类定义结束