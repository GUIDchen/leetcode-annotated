// 题目：3113. 边界元素是最大值的子数组数目（Find the Number of Subarrays Where Boundary Elements Are Maximum）
// 思路：单调栈维护「从栈底到栈顶严格递减」的 (数值, 该数值连续出现次数)；扫到 x 时栈顶 x 的计数就是「以 x 结尾且首尾都等于 x」的子数组数。
// 时间复杂度：O(n)，每个元素最多入栈、出栈各一次；空间复杂度：O(n)，栈最坏情况下保存所有不同的数值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfSubarrays(vector<int>& nums) {  // nums 是输入数组
        vector<pair<int, int>> stk;  // 单调栈，元素为 {数值, 该数值的连续出现次数}
        long long ans = 0;  // 累计合法子数组个数，数量可能超过 int 范围
        for (int x : nums) {  // 从左到右依次处理每个元素
            while (!stk.empty() && stk.back().first < x) {  // 栈顶比 x 小，之后不可能再成为边界上的最大值
                stk.pop_back();  // 弹出这些更小的元素
            }
            if (stk.empty() || stk.back().first > x) {  // 栈为空，或栈顶严格大于 x
                stk.push_back(make_pair(x, 1));  // 把 x 作为新的取值入栈，连续出现次数记为 1
            } else {  // 栈顶恰好等于 x
                stk.back().second++;  // 累加这个取值的连续出现次数
            }
            ans += stk.back().second;  // 以 x 结尾、首尾都等于 x 的合法子数组正好有「栈顶计数」个
        }
        return ans;  // 返回合法子数组的总数
    }
};