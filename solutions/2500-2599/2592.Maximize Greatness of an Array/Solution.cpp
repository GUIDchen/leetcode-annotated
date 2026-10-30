// 题目：2592. 最大化数组的伟大值（Maximize Greatness of an Array）
// 思路：排序后用双指针贪心匹配：把当前元素当作「更大的那个」，只要它大于尚未配对的最小元素 nums[i] 就配成一对并右移 i。
// 时间复杂度：O(n log n)，主要是排序开销；空间复杂度：O(log n)，排序所需的栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximizeGreatness(vector<int>& nums) {  // nums 是待重排的输入数组
        sort(nums.begin(), nums.end());  // 升序排序，使大小关系可以直接用下标比较
        int i = 0;  // i 是「尚未被配对的最小元素」的下标，同时也等于已经配对成功的数量
        for (int x : nums) {  // 把数组中的元素依次当作配对中「更大的那个」
            i += x > nums[i];  // 若 x 严格大于 nums[i]，说明能凑成一个伟大值，i 右移；否则 x 太小，只能跳过
        }
        return i;  // i 的最终值就是最大的伟大值
    }
};