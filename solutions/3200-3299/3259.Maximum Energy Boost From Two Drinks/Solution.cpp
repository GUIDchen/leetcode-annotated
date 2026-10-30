// 题目：3259. 超级饮料的最大强化能量（Maximum Energy Boost From Two Drinks）
// 思路：动态规划。f[i][0]、f[i][1] 表示第 i 天喝 A / B 时的最大总能量；要么继续喝同一种饮料并累加当天能量，要么切换到另一种饮料，但切换当天不增加能量（直接由前一天的另一状态转移）。
// 时间复杂度：O(n)，逐天递推一次；空间复杂度：O(n)，使用 n×2 的 dp 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {  // energyDrinkA / energyDrinkB 为两种饮料逐天的能量；返回可取得的最大总能量
        int n = energyDrinkA.size();  // n 为总天数
        vector<vector<long long>> f(n, vector<long long>(2));  // f[i][0] / f[i][1]：第 i 天喝 A / B 时能取得的最大总能量
        f[0][0] = energyDrinkA[0];  // 第 0 天只有一种选择，直接取 A 的能量
        f[0][1] = energyDrinkB[0];  // 第 0 天直接取 B 的能量
        for (int i = 1; i < n; ++i) {  // 从第 1 天开始按天递推
            f[i][0] = max(f[i - 1][0] + energyDrinkA[i], f[i - 1][1]);  // 继续喝 A 就累加 A[i]；或从 B 切换过来，切换当天不增加能量
            f[i][1] = max(f[i - 1][1] + energyDrinkB[i], f[i - 1][0]);  // 继续喝 B 就累加 B[i]；或从 A 切换过来，切换当天不增加能量
        }  // 递推结束
        return max(f[n - 1][0], f[n - 1][1]);  // 最后一天喝 A 或喝 B 取较大者即为答案
    }  // 方法结束
};  // 类定义结束
