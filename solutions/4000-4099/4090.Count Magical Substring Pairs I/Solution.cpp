// 题目：4090. 统计神奇子字符串对 I（Count Magical Substring Pairs I）
// 思路：枚举分界点 j，先倒序枚举左半子串 s[i..j]，把「恰好含 d 个不同字符」的左半子串个数记入 cnt[d]；再正序枚举右半子串 s[j+1..k]，用 cnt2 得到右半的不同字符数 d，直接累加 cnt[d]。左右两半不同字符数相等即为一个神奇子字符串对。
// 时间复杂度：O(n^3)，分界点、左端点、右端点各一层循环；空间复杂度：O(1)，cnt 固定 27 个格子，两张哈希表最多 26 个键。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countMagicalPairs(string s) {  // s：待统计的字符串；返回满足左右两半不同字符数相等的位置对个数
        int n = s.size();  // n 是字符串长度
        int ans = 0;  // ans 累计答案
        for (int j = 0; j < n - 1; j++) {  // 枚举分界点 j：左半是 s[0..j]，右半从 j+1 开始
            unordered_map<char, int> cnt1;  // cnt1：当前左半子串内各字符的出现次数
            int cnt[27]{};  // cnt[d]：恰好含 d 个不同字符的左半子串个数，d 最大为 26
            for (int i = j; i >= 0; i--) {  // 左端点 i 从 j 递减到 0，逐步扩充左半子串
                cnt1[s[i]]++;  // 把 s[i] 计入左半子串
                cnt[cnt1.size()]++;  // 当前左半子串的不同字符数为 cnt1.size()，对应桶加一
            }  // 左半部分统计完毕
            unordered_map<char, int> cnt2;  // cnt2：当前右半子串内各字符的出现次数
            for (int k = j + 1; k < n; k++) {  // 右端点 k 从 j+1 递增到 n-1，逐步扩充右半子串
                cnt2[s[k]]++;  // 把 s[k] 计入右半子串
                ans += cnt[cnt2.size()];  // 右半不同字符数为 cnt2.size()，与之相等的左半子串有 cnt[…] 个，全部计入答案
            }  // 右半部分枚举完毕
        }  // 分界点枚举结束
        return ans;  // 返回神奇子字符串对的总数
    }  // 方法结束
};  // 类定义结束