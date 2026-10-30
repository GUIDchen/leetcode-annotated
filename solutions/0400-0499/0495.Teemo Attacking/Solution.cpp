// 题目：495. 提莫攻击（Teemo Attacking）
// 思路：第一次攻击固定贡献 duration 秒，之后每相邻两次攻击只新增 min(duration, 间隔) 秒，逐段累加即得总中毒时长。
// 时间复杂度：O(n)，只需遍历一次时间序列；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {  // timeSeries 是递增的攻击时间点；duration 是每次中毒持续的秒数
        int ans = duration;  // 至少会完整度中毒一次，先用第一次攻击的时长打底
        int n = timeSeries.size();  // 攻击次数，用来确定循环上界
        for (int i = 1; i < n; ++i) {  // 从第二次攻击开始，逐段处理与上一次攻击的中毒重叠
            ans += min(duration, timeSeries[i] - timeSeries[i - 1]);  // 间隔不足 duration 时中毒会被刷新（取间隔），否则取完整的 duration
        }  // 所有相邻时间段都累加完毕
        return ans;  // 返回总中毒秒数
    }  // 方法体结束
};  // 类定义结束