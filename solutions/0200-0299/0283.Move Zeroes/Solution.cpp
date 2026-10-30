// 题目：283. 移动零（Move Zeroes）
// 思路：双指针，k 指向下一个非零元素该落的位置；遍历时把非零元素与 nums[k] 交换，零就被逐步挤到尾部。
// 时间复杂度：O(n) 一次遍历；空间复杂度：O(1)，原地交换。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void moveZeroes(vector<int>& nums) {  // nums：待原地调整的数组
        int k = 0, n = nums.size();  // k 是下一个非零元素的目标位置，n 是数组长度
        for (int i = 0; i < n; ++i) {  // 顺序扫描数组
            if (nums[i]) {  // 只有非零元素才需要前移
                swap(nums[i], nums[k++]);  // 与 k 位置交换后，非零元素前移、k 后移一位
            }
        }
    }
};
