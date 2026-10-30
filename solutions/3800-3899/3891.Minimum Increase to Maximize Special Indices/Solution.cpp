// 题目：3891. 最大化特殊下标数目的最少增加次数（Minimum Increase to Maximize Special Indices）
// 思路：特殊下标不能相邻，最多能取 ceil((n-2)/2) 个；用记忆化搜索从左往右决策，每个位置要么选为特殊下标（跳到 i+2），要么消耗一次“跳过”额度（跳到 i+1）。
// 时间复杂度：O(n)，每个状态只算一次；空间复杂度：O(n)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
private:  // 私有成员区
    vector<vector<long long>> f;  // 记忆化数组 f[i][j]：从下标 i 出发、跳过额度为 j 时的最小代价
    vector<int> nums;  // 保存输入数组，供 dfs 访问
    int n;  // 数组长度

public:  // 对外接口区
    long long minIncrease(vector<int>& nums) {  // nums：输入数组
        this->nums = nums;  // 把输入数组存为成员变量
        n = nums.size();  // 记录长度
        f.assign(n, vector<long long>(2, -1));  // 记忆化表初始化为 -1，表示尚未计算
        return dfs(1, (n & 1) ^ 1);  // 从下标 1 开始；n 为偶数时多给一次跳过额度，用来对齐奇偶相位
    }

    long long dfs(int i, int j) {  // dfs(i, j)：i 为当前下标，j 为剩余的跳过额度
        if (i >= n - 1) {  // 越过最后一个可能的下标，没有可选的“特殊”下标了
            return 0;  // 返回 0 代价
        }
        if (f[i][j] != -1) {  // 命中记忆化结果
            return f[i][j];  // 直接返回已算好的值
        }
        int cost = max(0, max(nums[i - 1], nums[i + 1]) + 1 - nums[i]);  // 把 nums[i] 抬到严格大于左右邻居所需的最少代价（不小于 0）
        long long ans = cost + dfs(i + 2, j);  // 选择 i 作为特殊下标，之后跳到 i+2（相邻下标不能再选）
        if (j > 0) {  // 还有跳过额度可用
            ans = min(ans, dfs(i + 1, 0));  // 放弃 i，消耗一次额度后从 i+1 继续，取两者较小值
        }
        return f[i][j] = ans;  // 记忆化并返回最优代价
    }  // 结束 dfs
};  // 结束类
