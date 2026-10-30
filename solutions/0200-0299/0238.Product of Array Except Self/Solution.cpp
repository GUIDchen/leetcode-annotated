// 题目：238. 除了自身以外数组的乘积（Product of Array Except Self）
// 思路：两趟前后缀积。第一趟让 ans[i] 等于 i 左侧所有元素的乘积，第二趟从右往左再乘上右侧所有元素的乘积。
// 时间复杂度：O(n)，只需两趟线性扫描；空间复杂度：O(1)，除返回数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> productExceptSelf(vector<int>& nums) {  // nums：输入数组，返回「除自身以外所有元素的乘积」
        int n = nums.size();  // 数组长度，两趟遍历共用
        vector<int> ans(n);  // 结果数组：先放左侧乘积，再乘上右侧乘积
        for (int i = 0, left = 1; i < n; ++i) {  // 第一趟从左到右：left 维护 nums[0..i-1] 的乘积
            ans[i] = left;  // 当前位置先只写入左侧乘积
            left *= nums[i];  // 把 nums[i] 并入 left，供下一个位置使用
        }
        for (int i = n - 1, right = 1; ~i; --i) {  // 第二趟从右到左：right 维护 nums[i+1..n-1] 的乘积；~i 等价于 i >= 0
            ans[i] *= right;  // 左侧乘积 * 右侧乘积，就是除自身以外的乘积
            right *= nums[i];  // 把 nums[i] 并入 right，供左边一个位置使用
        }
        return ans;  // 返回结果数组
    }
};  // 题解类定义结束