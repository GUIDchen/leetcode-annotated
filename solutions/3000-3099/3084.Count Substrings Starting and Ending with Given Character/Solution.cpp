// 题目：3084. 统计以给定字符开头和结尾的子字符串总数（Count Substrings Starting and Ending with Given Character）
// 思路：统计字符 c 出现次数 cnt，单字符子串有 cnt 个，任取两个 c 作为首尾又贡献 C(cnt,2) 个。
// 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubstrings(string s, char c) {  // s：原字符串；c：目标字符；返回以 c 开头且以 c 结尾的子字符串数目
        long long cnt = ranges::count(s, c);  // 统计字符 c 在 s 中出现的次数
        return cnt + cnt * (cnt - 1) / 2;  // 每个 c 自身构成 cnt 个单字符子串，任选两个 c 又构成 C(cnt,2) 个子串
    }
};