// 题目：453. 最小操作次数使数组元素相等（Minimum Moves to Equal Array Elements）
// 思路：每次把 n-1 个元素加一，等价于每次把 1 个元素减一；要让全部元素相等，只能都降到最小值，故答案为「总和 - 最小值 × n」。
// 时间复杂度：O(n)，一次遍历同时求和与最小值；空间复杂度：O(1)，只用两个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves(vector<int>& nums) {  // nums：长度至少为 1 的整数数组；返回使所有元素相等的最少操作次数
        int s = 0;  // s：数组元素的总和
        int mi = 1 << 30;  // mi：数组中的最小值，初值取一个足够大的数（2^30）
        for (int x : nums) {  // 一次遍历同时求总和与最小值
            s += x;  // 累加当前元素
            mi = min(mi, x);  // 用当前元素更新最小值
        }  // 结束遍历
        return s - mi * nums.size();  // 总和减去「最小值 × 元素个数」，即把所有元素降到最小值所需的步数
    }  // 结束 minMoves
};  // 结束 Solution 类