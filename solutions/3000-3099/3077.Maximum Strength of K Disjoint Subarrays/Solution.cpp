// 题目：3077. K 个不相交子数组的最大能量值（Maximum Strength of K Disjoint Subarrays）
// 思路：线性 DP。f[i][j][t] 表示「考虑前 i 个数、已凑出 j 个子数组、t 表示第 i 个数是否属于第 j 段」时的最大能量，逐元素做「不选 / 延续当前段 / 新开一段」三种转移。
// 时间复杂度：O(nk)，每个状态只做常数次转移；空间复杂度：O(nk)，把三维状态压成一维数组存储。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumStrength(vector<int>& nums, int k) {  // nums：输入数组；k：需要选择的子数组个数；返回最大能量值
        int n = nums.size();  // 数组长度
        const long long inf = LLONG_MIN / 2;  // 取极小值代表「不可达」，只用 LLONG_MIN 的一半，避免后续相加时下溢
        vector<long long> f((n + 1LL) * (k + 1) * 2, inf);  // 把 f[i][j][t] 压成一维：i 有 n+1 层、j 有 k+1 种、t 有 0/1 两种，初始全部不可达
        auto at = [&](int i, int j, int t) -> long long& {  // 用 lambda 封装一维下标的换算，写法上仍像三维数组；返回引用，可直接赋值
            return f[(i * (k + 1) + j) * 2 + t];  // 一维下标 = (i * (k+1) + j) * 2 + t
        };  // lambda 定义结束
        at(0, 0, 0) = 0;  // 边界：前 0 个数选 0 段且不在任何段中，能量为 0
        for (int i = 1; i <= n; i++) {  // i 表示当前考虑到前 i 个数，本轮新增的是 nums[i-1]
            int x = nums[i - 1];  // 当前元素的值
            for (int j = 0; j <= k; j++) {  // 枚举已经凑出的子数组段数 j
                long long sign = (j & 1) == 1 ? 1 : -1;  // 第 j 段的符号：j 为奇数取正、偶数取负，即 (-1)^(j+1)
                long long val = sign * x * (k - j + 1);  // 当前元素落在第 j 段时的贡献：符号 * 值 * 权重 (k - j + 1)
                at(i, j, 0) = max(at(i - 1, j, 0), at(i - 1, j, 1));  // 不把第 i 个数纳入任何段：从上一轮「不在段中」或「正在段中」两种状态转移
                at(i, j, 1) = max(at(i, j, 1), at(i - 1, j, 1) + val);  // 延续第 j 段：接到上一轮「正在第 j 段中」的状态后面，并与已有值取较大者
                if (j > 0) {  // 只有已经选了至少一段，才能考虑新开第 j 段
                    long long t = max(at(i - 1, j - 1, 0), at(i - 1, j - 1, 1)) + val;  // 新开一段的候选值：上一轮已选 j-1 段的最优状态再加当前元素的贡献
                    at(i, j, 1) = max(at(i, j, 1), t);  // 「延续旧段」与「新开一段」取较大者
                }
            }
        }
        return max(at(n, k, 0), at(n, k, 1));  // 答案：前 n 个数正好选了 k 段，最后一个数在段内或段外都允许，取较大者
    }
};
