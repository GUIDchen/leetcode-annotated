// 题目：3379. 转换数组（Transformed Array）
// 思路：把 nums[i] 看作环形偏移量。先对 n 取模得到相对位移，再补 n 抵消负数，最后整体 % n 得到合法下标。
// 时间复杂度：O(n)；空间复杂度：O(n)，用于存放返回数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    vector<int> constructTransformedArray(vector<int>& nums) {  // nums：输入数组；返回等长的转换后数组
        int n = nums.size();  // 数组长度，用于环形取模
        vector<int> ans(n);  // 答案数组，长度与输入一致
        for (int i = 0; i < n; ++i) {  // 枚举每个位置 i
            ans[i] = nums[(i + nums[i] % n + n) % n];  // 先对偏移量取模；+n 把负数拉回正区间；再 %n 保证下标落在 [0, n)
        }  // 枚举循环结束
        return ans;  // 返回转换后的数组
    }  // constructTransformedArray 方法结束
};  // Solution 类定义结束
