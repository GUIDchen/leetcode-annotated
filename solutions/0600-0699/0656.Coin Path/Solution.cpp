// 题目：656. 成本最小路径（Coin Path）
// 核心思路：从后往前 DP，f[i] = min(f[j] + coins[i])（i < j <= i+maxJump），再正向按 f 值还原字典序最小的路径。
// 时间复杂度：O(n * maxJump)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {  // 从下标 0 跳到 n-1，每步最多跨 maxJump 格，-1 表示该位置不能落脚
        int n = coins.size();  // n 是路径上的位置数
        vector<int> ans;  // ans 存放最终路径（题目要求 1 基下标）
        if (coins[n - 1] == -1) {  // 终点本身不可落脚，说明永远到不了终点
            return ans;  // 无解返回空路径
        }
        int f[n];  // f[i]：从 i 跳到终点的最小花费（包含 coins[i] 自身）
        const int inf = 1 << 30;  // inf 作为「不可达」的哨兵，1<<30 足够大且相加不会溢出
        f[n - 1] = coins[n - 1];  // 终点只能落在自己身上，花费就是它的硬币值
        for (int i = n - 2; ~i; --i) {  // 从后往前递推；~i 等价于 i >= 0
            f[i] = inf;  // 先假设从 i 到不了终点
            if (coins[i] != -1) {  // 只有 i 本身可以落脚时才可能转移
                for (int j = i + 1; j < min(n, i + maxJump + 1); ++j) {  // 枚举落点 j：最多跳 maxJump 格，且不越过最后一个位置
                    f[i] = min(f[i], f[j] + coins[i]);  // 用「j 之后的后续花费 + coins[i]」更新 f[i]
                }
            }
        }
        if (f[0] == inf) {  // 起点 0 无法到达终点
            return ans;  // 无解返回空路径
        }
        for (int i = 0, s = f[0]; i < n; ++i) {  // 正向还原路径：s 表示当前还需要的剩余花费，从 f[0] 开始
            if (f[i] == s) {  // f[i] == s 说明 i 一定在最优路径上（正向遍历天然保证字典序最小）
                s -= coins[i];  // 扣掉当前硬币花费，剩余目标变成下一跳的 f 值
                ans.push_back(i + 1);  // 记录 1 基下标
            }
        }
        return ans;  // 返回字典序最小的最优路径
    }
};  // 题解类定义结束