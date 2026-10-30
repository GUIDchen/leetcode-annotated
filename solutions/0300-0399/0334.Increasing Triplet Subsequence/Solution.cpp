// 题目：334. 递增的三元子序列（Increasing Triplet Subsequence）
// 核心思路：维护「最小值 mi」和「第二小值 mid」，从左到右扫描，一旦遇到大于 mid 的数，就说明存在 i<j<k 且 nums[i]<nums[j]<nums[k]。
// 时间复杂度：O(n)，只需一趟扫描；空间复杂度：O(1)，只用了两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool increasingTriplet(vector<int>& nums) {  // nums：输入数组，判断其中是否存在递增的三元子序列
        int mi = INT_MAX, mid = INT_MAX;  // mi 记录见过的最小值，mid 记录「前面已经出现过更小元素」的第二小值；初始化为无穷大表示尚未填值
        for (int num : nums) {  // 从左到右逐个扫描元素
            if (num > mid) return true;  // 当前值比 mid 还大，说明 mi < mid < num，三元组已经凑齐，直接返回 true
            if (num <= mi)  // 当前值不超过已知的最小值，只能用来刷新最小值
                mi = num;  // 刷新最小值 mi，此时 mid 保持不变
            else  // 否则当前值落在区间 (mi, mid] 内
                mid = num;  // 用它更新第二小值，为后面更大的元素做铺垫
        }  // for 循环结束
        return false;  // 扫描完所有元素仍未找到递增三元组，返回 false
    }  // 方法结束
};  // 类定义结束