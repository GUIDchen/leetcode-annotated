// 题目：3065. 超过阈值的最少操作数 I（Minimum Operations to Exceed Threshold Value I）
// 思路：每次操作只能删一个元素，所以最少操作数就是「小于 k 的元素个数」。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用一个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int k) {  // nums 是输入数组，k 是阈值，返回需要删除的元素个数
        int ans = 0;  // ans 累计小于 k 的元素个数
        for (int x : nums) {  // 逐个取出数组元素
            if (x < k) {  // 该元素小于阈值，必须被删掉
                ++ans;  // 计数加一
            }  // 判断结束
        }  // 遍历结束
        return ans;  // 返回最少操作数
    }  // 方法结束
};  // 类定义结束