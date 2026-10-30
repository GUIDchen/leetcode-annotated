// 题目：3098. 求出所有子序列的能量和（Find the Sum of Subsequence Powers）
// 思路：先排序使相邻元素之差成为最小差值候选，再记忆化搜索枚举长度恰为 k 的子序列，状态 (i, j, k, mi) 分别表示当前下标、上一个已选下标、还需选的个数与已选元素的最小差值。
// 时间复杂度：O(n^2·k)，状态数约为 n*n*k 量级且每个状态 O(1) 转移；空间复杂度：O(n^2·k)，即记忆化表的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfPowers(vector<int>& nums, int k) {  // nums：输入数组；k：子序列长度；返回所有长度恰为 k 的子序列能量之和对 1e9+7 取模
        unordered_map<long long, int> f;  // 记忆化表：把状态压缩成的长整型键映射到已算好的答案
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        int n = nums.size();  // 数组长度，供递归边界与剪枝使用
        sort(nums.begin(), nums.end());  // 先排序，这样相邻已选元素之差才能作为子序列能量（最小差值）的候选
        auto dfs = [&](this auto&& dfs, int i, int j, int k, int mi) -> int {  // 自引用泛型 lambda，this auto&& dfs 让函数能调用自身；i 为当前下标、j 为上一个已选元素下标、k 为还需选的个数、mi 为已选元素的最小差值
            if (i >= n) {  // 所有元素都已尝试完毕，递归终止
                return k == 0 ? mi : 0;  // 恰好选满 k 个才有能量 mi，否则该方案对答案贡献 0
            }  // 结束终止条件分支
            if (n - i < k) {  // 剩余元素个数不足以凑满 k 个，提前剪枝
                return 0;  // 该分支不可能产生合法子序列
            }  // 结束剪枝分支
            long long key = (1LL * mi) << 18 | (i << 12) | (j << 6) | k;  // 把 mi、i、j、k 四个状态压进一个 64 位整数当哈希键（各字段位宽互不重叠）
            if (f.contains(key)) {  // C++20 的 contains：该状态此前是否已经算过
                return f[key];  // 直接复用记忆化结果
            }  // 结束记忆化命中分支
            long long ans = dfs(i + 1, j, k, mi);  // 不选 nums[i] 的方案：状态完全不变，继续尝试下一个元素
            if (j == n) {  // j == n 表示当前是第一个被选中的元素，还不存在上一个元素
                ans += dfs(i + 1, i, k - 1, mi);  // 选它作为首元素，最小差值保持 mi 不变
            } else {  // 已经有上一个元素，需要更新最小差值
                ans += dfs(i + 1, i, k - 1, min(mi, nums[i] - nums[j]));  // 选它并让最小差值取 min(旧值, 与上一个元素之差)
            }  // 结束分支判断
            ans %= mod;  // 累加过程中随时取模，避免数值溢出
            f[key] = ans;  // 把本状态的答案写入记忆化表
            return f[key];  // 返回刚刚记忆化的结果
        };  // 结束 lambda 定义
        return dfs(0, n, k, INT_MAX);  // 从下标 0、没有上一个元素（用 n 表示）、还需选 k 个、最小差值为无穷大开始搜索
    }  // 结束题解方法
};  // 结束题解类
