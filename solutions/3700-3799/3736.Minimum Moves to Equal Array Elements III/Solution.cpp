// 3736. 最小操作次数使数组元素相等 III / Minimum Moves to Equal Array Elements III
// 核心思路：每次操作只能把某个元素加一，因此把所有元素补到数组最大值即可，答案是最大值乘以元素个数减去元素总和。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义 LeetCode 解法类
public:  // 公有接口
    int minMoves(vector<int>& nums) {  // 返回使所有元素相等所需的最小操作次数
        int n = nums.size();  // 数组长度
        int mx = 0;  // 数组中的最大值
        int s = 0;  // 数组元素之和
        for (int x : nums) {  // 遍历数组
            mx = max(mx, x);  // 维护最大值
            s += x;  // 累加元素和
        }  // 遍历结束
        return mx * n - s;  // 每个元素补到最大值的差值之和即为操作次数
    }  // 方法结束
};  // 类定义结束
