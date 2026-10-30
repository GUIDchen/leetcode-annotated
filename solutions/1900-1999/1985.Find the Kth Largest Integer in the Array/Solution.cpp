// 题目：1985. 找出数组中的第 K 大整数（Find the Kth Largest Integer in the Array）
// 思路：以字符串保存大整数，自定义比较规则（先比位数，位数相同再比字典序），再用 nth_element 做快速选择，第 k 大就落在下标 k-1。
// 时间复杂度：O(n) 平均，nth_element 平均线性；空间复杂度：O(1)，原地划分。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string kthLargestNumber(vector<string>& nums, int k) {  // nums：十进制数字字符串数组；k：要求的第 k 大
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), [](const string& a, const string& b) {  // 快速选择：平均线性地把「第 k 大」的元素放到下标 k-1 处
            return a.size() == b.size() ? a > b : a.size() > b.size();  // 位数多的整数一定更大；位数相同时字符串字典序就等于数值大小
        });  // lambda 比较器结束
        return nums[k - 1];  // 划分完成后下标 k-1 处即第 k 大的数字
    }  // 方法结束
};  // 类定义结束
