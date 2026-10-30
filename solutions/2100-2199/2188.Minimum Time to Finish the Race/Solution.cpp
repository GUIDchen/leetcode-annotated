// 题目：2188. 完成比赛的最少时间（Minimum Time to Finish the Race）
// 思路：先对每种轮胎预处理「同一套胎连续跑 j 圈」的最短耗时（单圈耗时超过换胎+首圈后继续跑就不划算，故 j 不超过 17），再对圈数做完全背包式 DP。
// 时间复杂度：O(T·18 + numLaps·18)；空间复杂度：O(18 + numLaps)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {  // tires：每种轮胎的(首圈耗时, 倍率)；changeTime：换胎耗时；numLaps：需要跑的圈数
        int cost[18];  // cost[j]：同一套胎连续跑 j 圈的最短耗时
        memset(cost, 0x3f, sizeof(cost));  // 用 0x3f3f3f3f 当无穷大初始化
        for (auto& e : tires) {  // 枚举每一种轮胎
            int f = e[0], r = e[1];  // f：首圈耗时；r：每多跑一圈的耗时倍率
            int s = 0;  // 从第 1 圈累计到当前圈的总耗时
            long long t = f;  // 当前这一圈的耗时，用 long long 防止倍乘溢出
            for (int i = 1; t <= changeTime + f; ++i) {  // 一旦单圈耗时超过「换胎 + 重新首圈」，继续跑就不划算，停止
                s += t;  // 累计连续跑 i 圈的总耗时
                cost[i] = min(cost[i], s);  // 用当前轮胎更新「连续跑 i 圈的最短耗时」
                t *= r;  // 下一圈耗时按倍率增长
            }  // 单种轮胎的枚举结束
        }  // 所有轮胎枚举结束
        int f[numLaps + 1];  // f[i]：跑完前 i 圈的最小总耗时（含换胎）
        memset(f, 0x3f, sizeof(f));  // 初始化为无穷大
        f[0] = -changeTime;  // 起点：0 圈还没换过胎，先把第一次换胎时间抵消掉
        for (int i = 1; i <= numLaps; ++i) {  // 从小到大递推每一圈的答案
            for (int j = 1; j < min(18, i + 1); ++j) {  // 枚举最后一段连续跑的圈数 j，最多 17 圈
                f[i] = min(f[i], f[i - j] + cost[j]);  // 用「前 i-j 圈 + 这一段 j 圈」转移
            }  // 枚举 j 结束
            f[i] += changeTime;  // 这一段开始前需要换一次胎，统一补上换胎耗时
        }  // 递推结束
        return f[numLaps];  // 跑完 numLaps 圈的最小耗时
    }  // 方法结束
};  // 类定义结束