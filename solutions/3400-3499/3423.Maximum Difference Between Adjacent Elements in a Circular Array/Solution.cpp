// 3423. 循环数组中相邻元素的最大差值 / Maximum Difference Between Adjacent Elements in a Circular Array
// 核心思路：先取首尾两个元素的绝对差（环的闭合边）作为初值，再线性扫描所有相邻对，边算边更新最大值
// 复杂度：时间 O(n)，空间 O(1)
class Solution {  // 定义题解类
public:  // 公有方法区
    int maxAdjacentDistance(vector<int>& nums) {  // 求循环数组中相邻元素绝对差的最大值
        int ans = abs(nums[0] - nums.back());  // 用首尾元素的差值初始化答案，覆盖环上的最后一条边
        for (int i = 1; i < nums.size(); ++i) {  // 枚举下标 i，考察 (i-1, i) 这一对相邻元素
            ans = max(ans, abs(nums[i] - nums[i - 1]));  // 用当前相邻对的绝对差更新最大值
        }  // 循环结束
        return ans;  // 返回最大绝对差
    }  // 方法结束
};  // 类定义结束
