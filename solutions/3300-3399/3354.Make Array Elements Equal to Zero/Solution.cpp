// 题目：3354. 使数组元素等于零（Make Array Elements Equal to Zero）
// 思路：先求总和 s，再从左向右用 l 累加已扫描元素之和；遇到 0 时比较 l 与 s-l，相等则两个方向都可行，相差 1 则只有一个方向可行。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用总和与左侧和两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countValidSelections(vector<int>& nums) {  // nums：输入数组，0 是可选起点
        int s = accumulate(nums.begin(), nums.end(), 0);  // 先求整个数组的元素总和，后续靠它推出右侧元素和 s - l
        int ans = 0, l = 0;  // ans：可行起点数；l：当前零左侧（已扫描元素）的元素和
        for (int x : nums) {  // 从左向右扫描，只在遇到 0 时结算
            if (x) {  // 非零元素，推进左侧和
                l += x;  // 把当前元素值累加到左侧和
            } else if (l * 2 == s) {  // 遇到 0 且左右两侧元素和相等：向左、向右两个起点都能把全数组减到 0
                ans += 2;  // 两个方向都可行，答案加 2
            } else if (abs(l * 2 - s) <= 1) {  // 两侧元素和相差不超过 1：只有元素和较大的那一侧出发才能精确清零
                ++ans;  // 至多一个方向可行，答案加 1
            }  // 结束 0 的分支判断
        }  // 结束扫描循环
        return ans;  // 返回可行起点总数
    }  // 结束题解方法
};  // 结束题解类
