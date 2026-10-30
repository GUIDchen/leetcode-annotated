// 题目：1781. 所有子字符串美丽值之和（Sum of Beauty of All Substrings）
// 思路：枚举子串左端点 i，右端点 j 向右扩展时增量维护 26 个字母的出现次数，每步重新扫描计数求最大最小频次之差并累加。
// 时间复杂度：O(n^2 * 26)，双重枚举子串，每次扫 26 个字母；空间复杂度：O(26)，即常数空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int beautySum(string s) {  // s 是只含小写字母的字符串
        int ans = 0;  // 累加所有子串的美丽值
        int n = s.size();  // 字符串长度
        int cnt[26];  // 每个字母在当前子串中出现的次数
        for (int i = 0; i < n; ++i) {  // 枚举子串左端点
            memset(cnt, 0, sizeof cnt);  // 换一个新的左端点，计数清零
            for (int j = i; j < n; ++j) {  // 右端点从 i 开始向右扩展
                ++cnt[s[j] - 'a'];  // 把新字符计入当前子串
                int mi = 1000, mx = 0;  // mi 记录最小频次（取一个足够大的初值），mx 记录最大频次
                for (int& v : cnt) {  // 扫描 26 个字母的计数
                    if (v > 0) {  // 只统计在当前子串中出现过的字母
                        mi = min(mi, v);  // 更新最小频次
                        mx = max(mx, v);  // 更新最大频次
                    }
                }
                ans += mx - mi;  // 该子串的美丽值就是最大频次减最小频次，累加
            }
        }
        return ans;  // 返回所有子串的美丽值之和
    }
};