// 题目：189. 轮转数组（Rotate Array）
// 思路：三次翻转。整体翻转后，前 k 个元素与后 n-k 个元素各自再翻转一次，即可得到右移 k 位的结果。
// 时间复杂度：O(n)，每个元素被翻转常数次；空间复杂度：O(1)，原地修改不使用额外数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void rotate(vector<int>& nums, int k) {  // nums 是待轮转数组，k 是右移位数
        int n = nums.size();  // 数组长度
        k %= n;  // k 可能大于 n，取模后才是真正的偏移量（也避免下面下标越界）
        reverse(nums.begin(), nums.end());  // 第一次翻转：整个数组逆序
        reverse(nums.begin(), nums.begin() + k);  // 第二次翻转：把前 k 个元素（原来的后 k 个）恢复正序
        reverse(nums.begin() + k, nums.end());  // 第三次翻转：把后面 n-k 个元素恢复正序
    }
};