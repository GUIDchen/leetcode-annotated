// 题目：1464. 数组中两元素的最大乘积（Maximum Product of Two Elements in an Array）
// 核心思路：枚举所有下标对 (i, j)，取 (nums[i] - 1) * (nums[j] - 1) 的最大值。
// 时间复杂度：O(n^2)，双重循环枚举所有配对；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProduct(vector<int>& nums) {  // nums 是输入数组，返回两元素减一后的最大乘积
        int ans = 0;  // 记录目前找到的最大乘积；元素都 ≥ 1，初值 0 安全
        int n = nums.size();  // 缓存数组长度，避免循环里反复取 size
        for (int i = 0; i < n; ++i) {  // 枚举第一个元素的下标
            for (int j = i + 1; j < n; ++j) {  // 枚举第二个元素的下标，从 i+1 开始避免重复配对与自配对
                ans = max(ans, (nums[i] - 1) * (nums[j] - 1));  // 按题目公式计算并尝试更新答案
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回最大乘积
    }  // 方法结束
};  // 类定义结束（分号不能省略）