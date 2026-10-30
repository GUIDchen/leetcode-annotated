// 题目：2475. 数组中不等三元组的数目（Number of Unequal Triplets in Array）
// 思路：三重循环枚举下标 i<j<k，只要三个位置的数值两两互不相等，就为答案贡献 1，最后返回计数。
// 时间复杂度：O(n^3)，三层循环；空间复杂度：O(1)，只用了常数级计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见，判题器据此调用
    int unequalTriplets(vector<int>& nums) {  // nums 是输入数组，返回满足条件的三元组个数
        int n = nums.size();  // n 为数组长度，作为三层循环的统一上界
        int ans = 0;  // 答案计数器，初始为 0
        for (int i = 0; i < n; ++i) {  // 枚举第一个下标 i
            for (int j = i + 1; j < n; ++j) {  // 枚举第二个下标 j，保证 j > i 以避免重复计数
                for (int k = j + 1; k < n; ++k) {  // 枚举第三个下标 k，保证 k > j，这样每组下标只被枚举一次
                    if (nums[i] != nums[j] && nums[j] != nums[k] && nums[i] != nums[k]) {  // 三个数两两不等：既 i≠j、j≠k，也 i≠k
                        ++ans;  // 满足条件，计数加一
                    }  // 分支结束
                }  // k 循环结束
            }  // j 循环结束
        }  // i 循环结束
        return ans;  // 返回满足条件的三元组总数
    }  // 方法结束
};  // 类定义结束