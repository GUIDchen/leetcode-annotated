// 3599. 划分数组得到最小 XOR（Partition Array to Minimize XOR）
// 核心思路：异或前缀和把每一段的异或转成区间异或，再做 DP：f[i][j] 表示前 i 个数分成 j 段时“各段异或最大值”的最小值。
// 复杂度：时间 O(n^2 · k)，空间 O(n · k)。
class Solution {  // 主解类
public:  // 对外接口
    int minXor(vector<int>& nums, int k) {  // 把数组划分成 k 段，使各段异或和中最大者尽量小
        int n = nums.size();  // 数组长度
        vector<int> g(n + 1);  // 异或前缀和数组
        for (int i = 1; i <= n; ++i) {  // 下标从 1 开始构造前缀
            g[i] = g[i - 1] ^ nums[i - 1];  // 异或前缀递推
        }  // 循环结束

        const int inf = numeric_limits<int>::max();  // 用一个极大值表示不可达状态
        vector f(n + 1, vector(k + 1, inf));  // DP 表 f[i][j]：前 i 个数分成 j 段的最小最大值
        f[0][0] = 0;  // 边界：0 个数分成 0 段，代价为 0

        for (int i = 1; i <= n; ++i) {  // 枚举前缀长度 i
            for (int j = 1; j <= min(i, k); ++j) {  // 段数 j 不能超过元素个数 i，也不能超过 k
                for (int h = j - 1; h < i; ++h) {  // 枚举最后一段的起点 h，前 h 个数分成 j-1 段
                    f[i][j] = min(f[i][j], max(f[h][j - 1], g[i] ^ g[h]));  // 转移：最后一段的区间异或与前面最大值取较大者，再对所有切法取最小
                }  // 循环结束
            }  // 循环结束
        }  // 循环结束

        return f[n][k];  // 返回前 n 个数分成 k 段的最优值
    }  // minXor 结束
};  // 类定义结束
