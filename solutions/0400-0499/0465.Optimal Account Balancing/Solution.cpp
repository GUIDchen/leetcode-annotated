// 题目：465. 最优账单平衡（Optimal Account Balancing）
// 思路：先把流水汇总成每人的净余额，再对非零余额做状压 DP：只对总和为 0 的子集，把 k 人平账的最少次数按子集拆分求最小值。
// 时间复杂度：O(3^m + m·2^m)，m 为净余额非零的人数（≤12）；空间复杂度：O(2^m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTransfers(vector<vector<int>>& transactions) {  // transactions 每项为 [付款人, 收款人, 金额]
        int g[12]{};  // g：每个人的净余额，下标即人编号，题目人数不超过 12
        for (auto& t : transactions) {  // 逐笔结算流水
            g[t[0]] -= t[2];  // 付款人余额减少
            g[t[1]] += t[2];  // 收款人余额增加
        }  // 全部流水处理完，g 中即为各人净欠/净收
        vector<int> nums;  // 只保留余额非零的人，余额为 0 的人无需参与平账
        for (int x : g) {  // 遍历每个人的净余额
            if (x) {  // 余额非零才需要转账
                nums.push_back(x);  // 收集到 nums 中
            }  // 结束余额判断
        }  // 结束遍历
        int m = nums.size();  // 真正需要平账的人数
        int f[1 << m];  // f[掩码]：把该子集内部平账所需的最少转账次数
        memset(f, 0x3f, sizeof(f));  // 初始化为极大值，表示暂不可达
        f[0] = 0;  // 空集合不需要任何转账
        for (int i = 1; i < 1 << m; ++i) {  // 枚举所有非空子集
            int s = 0;  // 该子集的余额总和
            for (int j = 0; j < m; ++j) {  // 逐位统计子集内的余额
                if (i >> j & 1) {  // 第 j 个人在子集内
                    s += nums[j];  // 累加他的余额
                }  // 结束位判断
            }  // 结束统计
            if (s == 0) {  // 只有总和为零的子集才可能内部平账
                f[i] = __builtin_popcount(i) - 1;  // k 个人平账至多需要 k-1 次转账
                for (int j = (i - 1) & i; j; j = (j - 1) & i) {  // 枚举 i 的所有真子集 j（标准子集枚举写法）
                    f[i] = min(f[i], f[j] + f[i ^ j]);  // 拆成 j 与 i^j 两部分分别平账，取更优
                }  // 结束子集枚举
            }  // 结束零和判断
        }  // 结束子集遍历
        return f[(1 << m) - 1];  // 全集对应的状态即为答案
    }  // 结束 minTransfers
};  // 结束 Solution 类