// 3487. 删除后的最大子数组元素和 / Maximum Unique Subarray Sum After Deletion
// 核心思路：若所有元素都不大于 0，最优只能保留最大元素；否则删除（或忽略）所有负数，并把不重复的正数全部累加，即可得到最大元素和。
// 复杂度：时间 O(n)，空间 O(n)（去重哈希集合）。
class Solution {  // 定义题解类
public:  // 公有接口
    int maxSum(vector<int>& nums) {  // 主函数：返回删除后不含重复元素的最大子数组元素和
        int mx = ranges::max(nums);  // 数组中的最大值
        if (mx <= 0) {  // 最大值都不大于 0，说明元素全为非正数
            return mx;  // 此时只能留下一个元素，取最大者
        }  // 结束非正数分支
        unordered_set<int> s;  // 记录已经选入的正数，避免重复累加
        int ans = 0;  // 去重后的正数之和
        for (int x : nums) {  // 遍历每个元素
            if (x < 0 || s.contains(x)) {  // 负数不选，已经选过的相同正数不再重复选
                continue;  // 跳过该元素
            }  // 结束筛选判断
            ans += x;  // 累加这个正数
            s.insert(x);  // 标记该正数已使用
        }  // 结束遍历
        return ans;  // 返回最大元素和
    }  // 结束 maxSum
};  // 结束 Solution 类
