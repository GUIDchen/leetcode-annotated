// 题目：724. 寻找数组的中心下标（Find Pivot Index）
// 思路：先求出总和作为「右侧和」，再从左往右遍历，每步先扣掉 nums[i]，此时 left/right 恰为 i 的左右两侧和，相等即答案。
// 时间复杂度：O(n)，一次求和加一次遍历；空间复杂度：O(1)，只用两个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int pivotIndex(vector<int>& nums) {  // nums：输入数组
        int left = 0, right = accumulate(nums.begin(), nums.end(), 0);  // left 为 i 左侧元素和，right 初始为整个数组的和
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右逐个尝试作为中心下标
            right -= nums[i];  // 先扣除 nums[i]，使 right 变成 i 右侧（不含 i）的元素和
            if (left == right) {  // 左侧和等于右侧和，i 就是中心下标
                return i;  // 题目要求最左边那个，找到即可返回
            }  // if 结束
            left += nums[i];  // 进入下一位置前，把 nums[i] 累加进左侧和
        }  // for 循环结束
        return -1;  // 遍历完仍没有中心下标
    }  // 方法结束
};  // 类定义结束