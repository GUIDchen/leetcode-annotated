// 3494. Find the Minimum Amount of Time to Brew Potions / 3494. 酿造药水需要的最少总时间
// 核心思路：按药水顺序 DP，f[i] 记录巫师 i 完成当前药水的时刻；每种药水先正向贪心求出最后一位巫师的完成时间，再反向回推使整条流水线尽量紧凑。
// 复杂度：时间 O(n * m)，其中 n 为巫师数、m 为药水数；空间 O(n)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    long long minTime(vector<int>& skill, vector<int>& mana) {  // skill 为各巫师单位时间处理量，mana 为各药水所需时间
        int n = skill.size();  // 巫师个数
        vector<long long> f(n);  // f[i] 表示巫师 i 完成当前药水的时刻，初始为 0 表示还未开工
        for (int x : mana) {  // 按顺序处理每一种药水
            long long tot = 0;  // 记录流水线上一位巫师完成当前药水的时刻
            for (int i = 0; i < n; ++i) {  // 正向贪心：依次安排每个巫师
                tot = max(tot, f[i]) + 1LL * skill[i] * x;  // 该巫师需等前一位完成且自己空闲，再加自身耗时 skill[i] * x
            }
            f[n - 1] = tot;  // 最后一位巫师的完成时刻即整瓶药水的完成时刻
            for (int i = n - 2; i >= 0; --i) {  // 反向回推，让前面的巫师尽量晚开工以留出空隙
                f[i] = f[i + 1] - 1LL * skill[i + 1] * x;  // 由后一位的开工时刻倒推自己的完成时刻
            }
        }
        return f[n - 1];  // 全部药水酿完后，最后一位巫师的完成时刻即总耗时
    }
};
