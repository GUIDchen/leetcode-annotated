// 题目：2400. 恰好移动 k 步到达某一位置的方法数目（Number of Ways to Reach a Position After Exactly k Steps）
// 思路：以“到目标的距离 i + 剩余步数 j”为状态做记忆化搜索，每步要么让距离加 1、要么让距离减 1（取绝对值）。
// 时间复杂度：O(k^2)，状态数为 k×k；空间复杂度：O(k^2)，记忆化数组 f 的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfWays(int startPos, int endPos, int k) {  // startPos：起点；endPos：终点；k：恰好要走 k 步
        const int mod = 1e9 + 7;  // 方案数对 1e9+7 取模，防止溢出
        int f[k + 1][k + 1];  // f[i][j]：距离为 i、还剩 j 步时的方案数，-1 表示尚未计算
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，作为“未计算”的标记
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // C++23 显式对象参数的递归 lambda：把自身作为第一个参数传入
            if (i > j || j < 0) {  // 距离已超过剩余步数，或剩余步数为负：不可能到达
                return 0;  // 这些状态贡献 0 种方案
            }
            if (j == 0) {  // 剩余步数为 0 时，是否到达取决于距离是否为 0
                return i == 0 ? 1 : 0;  // 距离为 0 记 1 种方案，否则 0 种
            }
            if (f[i][j] != -1) {  // 已经算过的状态
                return f[i][j];  // 直接返回缓存值
            }
            f[i][j] = (dfs(i + 1, j - 1) + dfs(abs(i - 1), j - 1)) % mod;  // 远离目标（距离 +1）或靠近目标（距离 -1，取绝对值防止为负），相加取模
            return f[i][j];  // 返回当前状态的方案数
        };
        return dfs(abs(startPos - endPos), k);  // 从起终点距离出发，走满 k 步
    }
};
