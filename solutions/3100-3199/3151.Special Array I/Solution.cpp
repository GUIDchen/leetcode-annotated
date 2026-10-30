// 题目：3151. 特殊数组 I（Special Array I）
// 思路：一次线性扫描，检查每一对相邻元素的奇偶性是否都不同。
// 时间复杂度：O(n)，只遍历一遍；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isArraySpecial(vector<int>& nums) {  // nums：输入数组，返回它是否为特殊数组
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，逐个与左邻居比较
            if (nums[i] % 2 == nums[i - 1] % 2) {  // 相邻两数奇偶性相同，违反「特殊数组」定义
                return false;  // 立刻返回 false
            }
        }
        return true;  // 所有相邻对的奇偶性都不同，返回 true
    }
};