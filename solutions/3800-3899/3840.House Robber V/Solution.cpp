// 3840. 打家劫舍 V / House Robber V（中等）
// 核心思路：线性 DP，f 表示不偷当前房屋的最大收益、g 表示偷当前房屋的最大收益；相邻两间颜色相同则不能同时偷，偷 i 只能接 f；颜色不同时偷 i 可以接 max(f, g)。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // LeetCode 要求的类名
public:  // 对外接口区
    long long rob(vector<int>& nums, vector<int>& colors) {  // 返回满足颜色限制的最大收益
        int n = nums.size();  // 房屋数量
        long long f = 0, g = nums[0];  // f：不偷第 0 间的收益；g：偷第 0 间的收益
        for (int i = 1; i < n; i++) {  // 从第 1 间开始逐间递推
            if (colors[i - 1] == colors[i]) {  // 相邻两间颜色相同，不能同时偷
                long long gg = f + nums[i];  // 偷第 i 间时，第 i-1 间必须不偷，只能接 f
                f = max(f, g);  // 不偷第 i 间：从前两个状态的较优值继承
                g = gg;  // 更新偷第 i 间的最优收益
            } else {  // 颜色不同，可以连续偷两间
                long long gg = max(f, g) + nums[i];  // 偷第 i 间可以接前面任一状态
                f = max(f, g);  // 不偷第 i 间：从前两个状态的较优值继承
                g = gg;  // 更新偷第 i 间的最优收益
            }  // 分支结束
        }  // 循环结束
        return max(f, g);  // 最后一间偷与不偷取较大者
    }  // 方法结束
};  // 类定义结束
