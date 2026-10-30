// 3914. Minimum Operations to Make Array Non Decreasing | 使数组非递减需要的最小累计值（中等）
// 核心思路：从左往右检查每一对相邻元素，凡是出现下降（nums[i-1] > nums[i]）的地方，就必须把这一段补齐 nums[i-1] - nums[i] 次；把所有下降落差累加起来就是最小操作次数。
// 复杂度：时间 O(n)，一次线性扫描；空间 O(1)，只用了累计变量。
class Solution {  // 定义题解类
public:  // 公有接口
    long long minOperations(vector<int>& nums) {  // 返回把数组变成非递减所需的最小操作次数
        long long ans = 0;  // 累计操作次数，结果可能很大，用 long long
        for (int i = 1; i < nums.size(); ++i) {  // 从左往右检查每一对相邻元素
            ans += max(nums[i - 1] - nums[i], 0);  // 出现下降时累加落差，未下降时 max 取 0 不计入
        }  // 循环结束
        return ans;  // 返回最小操作次数
    }  // 方法结束
};  // 类定义结束
