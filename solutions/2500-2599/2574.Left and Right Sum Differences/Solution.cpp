// 题目：2574. 左右元素和的差值（Left and Right Sum Differences）
// 思路：先用一次遍历求出数组总和作为右侧和，再从前往后移动分界线，同步维护左侧和与右侧和。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，用于存放答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> leftRightDifference(vector<int>& nums) {  // nums：输入数组，返回每个位置左右元素和的差值
        int l = 0, r = 0;  // l 是左侧元素和，r 是右侧元素和
        for (int x : nums) {  // 先遍历一遍求出数组总和
            r += x;  // 把每个元素累加到右侧和
        }
        int n = nums.size();  // 数组长度
        vector<int> ans(n);  // 答案数组，长度与输入数组相同
        for (int i = 0; i < n; ++i) {  // 从左到右依次计算每个位置
            r -= nums[i];  // 当前元素不再属于右侧，先从右侧和中减去
            ans[i] = abs(l - r);  // 保存左右和之差的绝对值
            l += nums[i];  // 当前元素加入左侧和，供下一个位置使用
        }
        return ans;  // 返回答案数组
    }
};
