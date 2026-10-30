// 题目：3119. 最大数量的可修复坑洼（Maximum Number of Potholes That Can Be Fixed，会员题）
// 思路：统计每种长度的连续坑洼段；按段长从大到小贪心，修完一段长 k 的坑洼要 k+1 预算、得 k 个坑，预算不够就把它拆成更短的段。
// 时间复杂度：O(n)，扫描道路一次 + 按段长倒序枚举；空间复杂度：O(n)，cnt 数组按段长计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxPotholes(string road, int budget) {  // road：道路字符串（'x' 为坑洼、'.' 为完好）；budget：可用预算
        road.push_back('.');  // 末尾补一个非坑洼字符，保证最后一段连续坑洼也能被结算
        int n = road.size();  // 补齐后的长度，同时也是段长的上限
        vector<int> cnt(n);  // cnt[k]：长度为 k 的连续坑洼段共有多少段
        int k = 0;  // 当前连续坑洼的长度
        for (char& c : road) {  // 顺序扫描道路上的每个字符
            if (c == 'x') {  // 遇到坑洼，当前段长加一
                ++k;  // 遇到完好路面，且之前累计过坑洼
            } else if (k) {  // 这个长度的坑洼段又出现一次
                ++cnt[k];  // 段长清零，开始统计下一段
                k = 0;  // 结束分支
            }  // 结束扫描
        }  // 记录能修好的坑洼总数
        int ans = 0;  // 从长段到短段贪心，段长为 0 或预算用尽即停止
        for (k = n - 1; k && budget; --k) {  // 修一整段长 k 的坑洼要 k+1 预算（末尾还要补一格），可获得 k 个坑洼
            int t = min(budget / (k + 1), cnt[k]);  // 这段最多能修多少次，受预算与段数共同限制
            ans += t * k;  // 累加修好的坑洼数
            budget -= t * (k + 1);  // 扣除对应预算
            cnt[k - 1] += cnt[k] - t;  // 没修的段拆成长度 k-1 的段，留给后面继续处理
        }  // 结束贪心循环
        return ans;  // 返回能修好的最大坑洼数
    }  // 结束 maxPotholes
};  // 类定义结束