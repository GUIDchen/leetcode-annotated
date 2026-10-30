// 题目：1563. 石子游戏 V（Stone Game V）
// 思路：区间 DP + 记忆化。枚举分割点，若两段和不等则 Bob 丢弃较大的一段，只能在小的一段继续递归；两段相等时两种选择都尝试。用前缀和 O(1) 求段和，并用上界剪枝减少枚举。
// 时间复杂度：O(n^3)，区间 O(n^2) × 分割点 O(n)，剪枝后更快；空间复杂度：O(n^2)，记忆化数组与前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int stoneGameV(vector<int>& stoneValue) {  // stoneValue：每堆石子的价值
        int n = stoneValue.size();  // n 为石子堆数
        int s[n + 1];  // 前缀和数组：s[i] 表示前 i 堆石子之和
        s[0] = 0;  // 空前缀和为 0
        for (int i = 0; i < n; i++) {  // 从左往右累加，构造前缀和
            s[i + 1] = s[i] + stoneValue[i];  // 由前一项递推当前前缀和
        }  // 循环体结束
        int f[n][n];  // f[i][j] 记忆化区间 [i, j] 能取得的最大分数
        memset(f, -1, sizeof(f));  // 全部置为 -1，表示该区间尚未计算
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // C++23 显式对象参数写法，让 lambda 内部可以递归调用自己
            if (i >= j) {  // 只剩一段或空区间时无法继续分割
                return 0;  // 得分为 0
            }  // if 结束
            if (f[i][j] != -1) {  // 该区间之前算过
                return f[i][j];  // 直接返回记忆值，避免重复计算
            }  // if 结束
            int ans = 0, l = 0, r = s[j + 1] - s[i];  // ans 当前最优；l 左段和；r 右段和，初始为整段之和
            for (int k = i; k < j; ++k) {  // 枚举分割点 k：左段 [i, k]，右段 [k+1, j]
                l += stoneValue[k];  // 左段和加入 stoneValue[k]
                r -= stoneValue[k];  // 右段和减去 stoneValue[k]
                if (l < r) {  // 左段更小，Bob 会丢掉右段，只能在左段继续游戏
                    if (ans > l * 2) {  // 剪枝：左段贡献上限是 l + l，已经不可能超过 ans
                        continue;  // 这个分割点无望，跳过
                    }  // if 结束
                    ans = max(ans, l + dfs(i, k));  // 取左段和加上左段内部能得到的最大分数
                } else if (l > r) {  // 右段更小，Bob 会丢掉左段，只能在右段继续游戏
                    if (ans > r * 2) {  // 剪枝：右段贡献上限是 r + r，已经不可能超过 ans
                        break;  // 之后 r 只会更小，更不可能更优，直接跳出循环
                    }  // if 结束
                    ans = max(ans, r + dfs(k + 1, j));  // 取右段和加上右段内部能得到的最大分数
                } else {  // 两段和相等，Bob 可以任选一段
                    ans = max({ans, l + dfs(i, k), r + dfs(k + 1, j)});  // 两种选法都尝试，取最大
                }  // 分支结束
            }  // 分割点枚举结束
            return f[i][j] = ans;  // 记忆化并返回区间最优值
        };  // lambda 定义结束
        return dfs(0, n - 1);  // 从整个区间开始求解
    }  // 方法结束
};  // 类定义结束
