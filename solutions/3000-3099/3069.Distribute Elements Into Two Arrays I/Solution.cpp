// 题目：3069. 将元素分配到两个数组中 I（Distribute Elements Into Two Arrays I）
// 核心思路：按题意模拟——两个数组分别以 nums[0]、nums[1] 起步，之后每个元素放到「末尾元素更大」的那个数组的末尾，最后把两数组首尾拼接。
// 时间复杂度：O(n)，每个元素只比较与追加一次；空间复杂度：O(n)，两个数组共保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> resultArray(vector<int>& nums) {  // nums：输入数组（长度至少为 2）；返回拼接后的结果数组
        int n = nums.size();  // 元素总个数，后面循环需要用到
        vector<int> arr1 = {nums[0]};  // arr1 以第一个元素作为初始唯一元素
        vector<int> arr2 = {nums[1]};  // arr2 以第二个元素作为初始唯一元素
        for (int k = 2; k < n; ++k) {  // 从下标 2 开始，把剩下的元素依次分配
            if (arr1.back() > arr2.back()) {  // 比较两个数组当前的末尾元素，谁更大就放进谁
                arr1.push_back(nums[k]);  // arr1 末尾更大（或相等时也归 arr1），把当前元素追加到 arr1
            } else {  // 否则（arr2 末尾严格更大）
                arr2.push_back(nums[k]);  // 当前元素追加到 arr2 末尾
            }
        }
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());  // 把 arr2 的全部元素依次追加到 arr1 末尾，得到最终拼接结果
        return arr1;  // 返回拼接后的数组
    }
};