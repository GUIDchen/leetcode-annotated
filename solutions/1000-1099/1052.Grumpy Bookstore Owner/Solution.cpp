// 题目：1052. 爱生气的书店老板（Grumpy Bookstore Owner）
// 思路：固定收益是老板不生气时段的顾客数；再用长度 minutes 的滑动窗口，统计生气时段中被技巧覆盖的顾客数，取窗口和的最大值。
// 时间复杂度：O(n)，一次滑动窗口扫描；空间复杂度：O(1)，只用了常数个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {  // customers：每分钟顾客数；grumpy：1 表示该分钟老板生气；minutes：可抑制生气的最长分钟数
        int cnt = 0;  // 当前窗口内因老板生气而流失的顾客数（可被技巧挽回的部分）
        int tot = 0;  // 所有「不生气」分钟内本来就满意的顾客总数
        for (int i = 0; i < minutes; ++i) {  // 先建立第一个长度为 minutes 的窗口
            cnt += customers[i] * grumpy[i];  // 生气分钟的顾客计入窗口收益
            tot += customers[i] * (grumpy[i] ^ 1);  // grumpy[i] ^ 1 即取反：不生气分钟的顾客计入固定收益
        }  // 首个窗口统计完毕
        int mx = cnt;  // 窗口能挽回的最多顾客数
        int n = customers.size();  // 总分钟数
        for (int i = minutes; i < n; ++i) {  // 窗口右移，每次进一个、出一个
            cnt += customers[i] * grumpy[i];  // 新进入窗口的那一分钟
            cnt -= customers[i - minutes] * grumpy[i - minutes];  // 移出窗口的那一分钟
            mx = max(mx, cnt);  // 更新窗口内可挽回顾客数的最大值
            tot += customers[i] * (grumpy[i] ^ 1);  // 同时累加这一分钟的固定满意顾客
        }  // 滑动结束
        return tot + mx;  // 固定满意数 + 技巧窗口最多挽回的顾客数
    }  // 方法结束
};  // 题解类结束