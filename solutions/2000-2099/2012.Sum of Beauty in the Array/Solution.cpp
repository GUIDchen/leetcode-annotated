// 题目：2012. 数组美丽值求和（Sum of Beauty in the Array）
// 思路：先用一遍倒序扫描求出后缀最小值 right[i]，再正序扫描并用 l 维护前缀最大值，按题目两类条件累加美丽值。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，right 数组保存后缀最小值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfBeauties(vector<int>& nums) {  // nums：下标从 0 开始的整数数组；返回所有下标美丽值之和
        int n = nums.size();  // n 为数组长度，后面多处用到
        vector<int> right(n, nums[n - 1]);  // right[i] 用来保存 nums[i..n-1] 的最小值，先全部填成最后一个元素
        for (int i = n - 2; i; --i) {  // 从右往左填表；i 为 0 时条件为假，循环停止
            right[i] = min(right[i + 1], nums[i]);  // 后缀最小值递推：取当前元素与右侧后缀最小值的较小者
        }  // 后缀最小值预处理结束
        int ans = 0;  // ans 累加所有下标的美丽值
        for (int i = 1, l = nums[0]; i < n - 1; ++i) {  // 只看中间下标 1..n-2；l 是 nums[0..i-1] 的最大值
            int r = right[i + 1];  // r 是 nums[i+1..n-1] 的最小值
            if (l < nums[i] && nums[i] < r) {  // 第一类：严格大于左侧所有元素且严格小于右侧所有元素
                ans += 2;  // 这种情况美丽值为 2
            } else if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1]) {  // 第二类：只要求严格大于左邻且严格小于右邻
                ans += 1;  // 这种情况美丽值为 1
            }  // 两类分支结束
            l = max(l, nums[i]);  // 把当前元素并入前缀最大值，供下一轮使用
        }  // 主循环结束
        return ans;  // 返回美丽值总和
    }  // 方法结束
};  // 类定义结束