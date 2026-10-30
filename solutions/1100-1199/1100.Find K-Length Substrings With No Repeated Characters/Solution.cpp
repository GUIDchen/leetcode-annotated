// 题目：1100. 长度为 K 的无重复字符子串（Find K-Length Substrings With No Repeated Characters）
// 思路：维护长度为 k 的滑动窗口与字符计数表，窗口内不同字符数等于 k 就说明没有重复。
// 时间复杂度：O(n)，每个字符进出窗口各一次；空间复杂度：O(k)，计数表最多存 k 个不同字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numKLenSubstrNoRepeats(string s, int k) {  // s：源字符串；k：目标子串长度
        int n = s.size();  // 字符串长度
        if (n < k) {  // 长度不足 k 时不可能有长度为 k 的子串
            return 0;  // 直接返回 0
        }  // if 结束
        unordered_map<char, int> cnt;  // 窗口内每个字符的出现次数
        for (int i = 0; i < k; ++i) {  // 先把第一个长度为 k 的窗口装满
            ++cnt[s[i]];  // 第 i 个字符计数加一
        }  // for 结束
        int ans = cnt.size() == k;  // 不同字符数等于 k 等价于窗口内无重复，bool 转 0 / 1 作为初始答案
        for (int i = k; i < n; ++i) {  // 窗口右端从 k 开始滑动，i 是新的右端点
            ++cnt[s[i]];  // 新字符进入窗口
            if (--cnt[s[i - k]] == 0) {  // 最左侧字符离开窗口，计数减到 0 就删除这个键
                cnt.erase(s[i - k]);  // 删除后 cnt.size() 才等于窗口内真实的不同字符数
            }  // if 结束
            ans += cnt.size() == k;  // 再判断一次当前窗口是否无重复，并累加
        }  // for 结束
        return ans;  // 返回满足条件的子串个数
    }  // 方法结束
};  // 类定义结束