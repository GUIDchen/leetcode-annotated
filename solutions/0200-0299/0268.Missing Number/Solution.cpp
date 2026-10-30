// 题目：268. 丢失的数字（Missing Number）
// 思路：把 0..n 与数组元素全部异或，成对出现的数两两抵消，剩下的就是缺失的那个。
// 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int missingNumber(vector<int>& nums) {  // nums 是缺失了一个数、长度为 n 的 0..n 排列
        int n = nums.size();  // n 既是从 0 到 n 共 n+1 个数中的最大值，也是数组长度
        int ans = n;  // 先把 n 作为异或初值，后面再把 0..n-1 与数组元素配对异或
        for (int i = 0; i < n; ++i) {  // 遍历数组的每个位置
            ans ^= (i ^ nums[i]);  // 把下标 i 与元素 nums[i] 一起异或，配对相同的数会抵消
        }  // 循环结束，ans 里只剩那个多出来的下标，即缺失的数
        return ans;  // 返回缺失的那个数
    }  // 方法结束
};  // 类定义结束