// 题目：1799. N 次操作后的最大分数和（Maximize Score After N Operations）
// 思路：状压 DP，f[mask] 表示「已用元素集合为 mask」时的最大得分；已用个数为偶数时，枚举最后取出的两个下标 i、j，本轮倍数正好是 cnt/2，转移为 f[mask] = max(f[mask], f[mask 去掉 i 和 j] + cnt/2 * gcd(i, j))。
// 时间复杂度：O(2^m · m^2)，m = 2n 为元素个数；空间复杂度：O(2^m + m^2)，DP 数组与 gcd 表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int maxScore(vector<int>& nums) {  // nums：长度为 2n 的数组，返回 n 次操作的最大得分和
        int m = nums.size();  // 元素个数，必为偶数 2n
        int g[m][m];  // g[i][j]：下标 i、j 两个数的最大公约数
        for (int i = 0; i < m; ++i) {  // 预处理所有数对
            for (int j = i + 1; j < m; ++j) {  // 只计算上三角 i < j，省一半空间与时间
                g[i][j] = gcd(nums[i], nums[j]);  // 计算并缓存 gcd
            }  // 内层循环结束
        }  // 外层循环结束
        int f[1 << m];  // 状压 DP 数组：f[mask] 是已用集合 mask 的最大得分
        memset(f, 0, sizeof f);  // 全部初始化为 0
        for (int k = 0; k < 1 << m; ++k) {  // 掩码从小到大枚举，转移来源一定比 k 小，顺序天然正确
            int cnt = __builtin_popcount(k);  // 当前已用掉的元素个数
            if (cnt % 2 == 0) {  // 只有偶数个才是某轮操作结束后的合法状态
                for (int i = 0; i < m; ++i) {  // 枚举这一轮的第一个下标 i
                    if (k >> i & 1) {  // i 必须已经在集合中
                        for (int j = i + 1; j < m; ++j) {  // 枚举第二个下标 j，只取 i < j 避免重复
                            if (k >> j & 1) {  // j 也必须在集合中
                                f[k] = max(f[k], f[k ^ (1 << i) ^ (1 << j)] + cnt / 2 * g[i][j]);  // 把 i、j 当作最后一对取走，本轮倍数为 cnt / 2
                            }  // if 结束
                        }  // j 循环结束
                    }  // if 结束
                }  // i 循环结束
            }  // 偶数状态分支结束
        }  // 掩码枚举结束
        return f[(1 << m) - 1];  // 所有元素都用完时的最大得分
    }  // 方法结束
};  // 类定义结束