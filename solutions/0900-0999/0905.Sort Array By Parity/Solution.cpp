// 题目：905. 按奇偶排序数组（Sort Array By Parity）
// 核心思路：双指针，左指针找奇数、右指针找偶数，两者都找到就交换，一次扫描把偶数全部换到前面。
// 时间复杂度：O(n)，每个元素最多被访问一次；空间复杂度：O(1)，只在原数组上原地交换。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    vector<int> sortArrayByParity(vector<int>& nums) {  // nums：待重排的数组；返回偶数在前、奇数在后的数组
        int i = 0, j = nums.size() - 1;  // 双指针：i 从左找奇数，j 从右找偶数
        while (i < j) {  // 两个指针相遇时结束
            if (nums[i] % 2 == 0) {  // 左端已经是偶数，位置正确
                ++i;  // 左指针右移，继续检查下一个
            } else if (nums[j] % 2 == 1) {  // 左端是奇数，再看右端是否也是奇数
                --j;  // 右端奇数位置正确，右指针左移
            } else {  // 左端是奇数、右端是偶数，两者需要交换
                swap(nums[i++], nums[j--]);  // 交换后两指针同时向中间收缩
            }  // 结束分支
        }  // 结束双指针扫描
        return nums;  // 返回重排后的数组
    }  // 结束 sortArrayByParity
};  // 结束 Solution 类