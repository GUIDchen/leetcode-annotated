// 题目：3361. 两个字符串的切换距离（Shift Distance Between Two Strings）
// 思路：对 26 个字母分别做向右（nextCost）与向左（previousCost）两圈的前缀和，任意一段移动代价可 O(1) 求出；每位取两个方向中更便宜的一种累加。
// 时间复杂度：O(n + 26)，n 为串长；空间复杂度：O(26)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露题解方法
    long long shiftDistance(string s, string t, vector<int>& nextCost, vector<int>& previousCost) {  // s、t：起止字符串；nextCost/previousCost：每个字母向右/向左走一步的代价
        int m = 26;  // 字母表大小 26
        vector<long long> s1((m << 1) + 1);  // 向右切换的前缀代价表，长度 2m+1 以支持跨过 z 绕环
        vector<long long> s2((m << 1) + 1);  // 向左切换的前缀代价表，同样长度 2m+1
        for (int i = 0; i < (m << 1); ++i) {  // 预先算好两圈的前缀和，之后任意区间可就近取差
            s1[i + 1] = s1[i] + nextCost[i % m];  // 向右：第 i 步的代价取自字母 i%m
            s2[i + 1] = s2[i] + previousCost[(i + 1) % m];  // 向左：第 i 步是从字母 i+1 走回 i，代价取 previousCost[(i+1)%m]
        }

        long long ans = 0;  // 累计总切换距离
        for (int i = 0; i < s.size(); ++i) {  // 逐位处理两个字符串
            int x = s[i] - 'a';  // 起点字母编号 0..25
            int y = t[i] - 'a';  // 终点字母编号 0..25
            long long c1 = s1[y + (y < x ? m : 0)] - s1[x];  // 只用向右操作的代价；y < x 时需要绕一整圈，终点下标整体加 m
            long long c2 = s2[x + (x < y ? m : 0)] - s2[y];  // 只用向左操作的代价；x < y 时需要绕一整圈，起点下标整体加 m
            ans += min(c1, c2);  // 该位置取两个方向中更便宜的代价累加
        }

        return ans;  // 返回总切换距离
    }  // 题解方法结束
};  // 题解类结束
