// 题目：977. 有序数组的平方（Squares of a Sorted Array）
// 思路：双指针从两端向中间取绝对值较大者，其平方最大，从答案末尾往前填即可保持非递减。
// 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sortedSquares(vector<int>& nums) {  // nums：已按非递减排序的数组，返回每个元素平方后仍按非递减排序的结果
        int n = nums.size();  // n 为数组长度
        vector<int> ans(n);  // ans 预分配 n 个位置，从后往前填，保证结果非递减
        for (int i = 0, j = n - 1, k = n - 1; i <= j; --k) {  // i 指向左端，j 指向右端，k 是答案中待填位置；每次循环只填一个位置
            int a = nums[i] * nums[i];  // 左端元素的平方
            int b = nums[j] * nums[j];  // 右端元素的平方
            if (a > b) {  // 平方较大的那个一定是当前剩余元素中最大的
                ans[k] = a;  // 把较大的平方填到答案的末尾位置
                ++i;  // 左端已用掉，左指针右移
            } else {  // 否则右端的平方更大
                ans[k] = b;  // 把右端的平方填到答案的末尾位置
                --j;  // 右端已用掉，右指针左移
            }  // if-else 结束
        }  // for 循环结束
        return ans;  // 返回构造好的答案
    }  // 题解方法结束
};  // Solution 类结束