// 3637. 三段式数组 I / Trionic Array I
// 核心思路：用指针依次找出严格递增段、严格递减段、再一个严格递增段，三段都非空且恰好走到末尾即为三段式数组
// 时间复杂度 O(n)，空间复杂度 O(1)
//
class Solution {  // 题目要求实现的类
public:  // 对外接口
    bool isTrionic(vector<int>& nums) {  // 判断数组能否拆成严格递增、严格递减、严格递增三段
        int n = nums.size();  // n 为数组长度
        int p = 0;  // p 指向第一段（递增段）的末尾
        while (p < n - 2 && nums[p] < nums[p + 1]) {  // 先找最长的严格递增前缀，留出后两段的空间
            p++;  // 指针右移
        }  // 循环结束
        if (p == 0) {  // 递增段为空则不合法
            return false;  // 返回 false
        }  // if 结束
        int q = p;  // q 从 p 出发，寻找中间的递减段
        while (q < n - 1 && nums[q] > nums[q + 1]) {  // 再找严格递减段
            q++;  // 指针右移
        }  // 循环结束
        if (q == p || q == n - 1) {  // 递减段为空，或递减段直接走到末尾（缺第三段）都不合法
            return false;  // 返回 false
        }  // if 结束
        while (q < n - 1 && nums[q] < nums[q + 1]) {  // 最后找第三段的严格递增
            q++;  // 指针右移
        }  // 循环结束
        return q == n - 1;  // 只有恰好走到最后一个下标，才说明恰好是合法的三段式
    }  // 函数结束
};  // 类定义结束