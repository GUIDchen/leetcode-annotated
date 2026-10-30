// 3196. 最大化子数组的总成本（Maximize Total Cost of Alternating Subarrays）
// 核心思路：记忆化搜索。f[i][j] 表示从下标 i 开始、j 表示 nums[i] 是否可继承负号时的最大总成本；要么让 nums[i] 当新子数组首项取正号，要么继承负号。
// 复杂度：时间 O(n)，空间 O(n)

class Solution {  // 定义题解类
public:  // 公开接口
    long long maximumTotalCost(vector<int>& nums) {  // 返回把 nums 划分成若干交替子数组后的最大总成本
        int n = nums.size();  // 记录数组长度
        long long f[n][2];  // 记忆化数组：f[i][j] 表示从下标 i 开始、j 标识 nums[i] 能否取负号的最优值
        fill(f[0], f[n], LLONG_MIN);  // 全部初始化为 LLONG_MIN，表示该状态尚未计算
        auto dfs = [&](this auto&& dfs, int i, int j) -> long long {  // 定义递归函数：i 为当前下标，j 为 0/1 表示 nums[i] 能否取负号
            if (i >= n) {  // 边界：已经越过最后一个元素
                return 0;  // 空后缀的成本为 0
            }  // 结束边界分支
            if (f[i][j] != LLONG_MIN) {  // 该状态之前算过
                return f[i][j];  // 直接返回记忆化结果
            }  // 结束重复状态判断
            f[i][j] = nums[i] + dfs(i + 1, 1);  // 方案一：nums[i] 作为新子数组首项取正号，下一项状态放开为 1
            if (j) {  // 若当前元素允许取负号（与前一项同处一个子数组）
                f[i][j] = max(f[i][j], -nums[i] + dfs(i + 1, 0));  // 方案二：nums[i] 取负号，下一项只能取正号（状态 0），取两者较大值
            }  // 结束方案二分支
            return f[i][j];  // 返回当前状态的最优值
        };  // 递归函数定义结束
        return dfs(0, 0);  // 从下标 0 开始，首项必须取正号（j = 0）
    }  // 方法结束
};  // 类定义结束
