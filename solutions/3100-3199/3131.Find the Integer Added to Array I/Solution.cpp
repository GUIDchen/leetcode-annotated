// 题目：3131. 找出与数组相加的整数 I（Find the Integer Added to Array I）
// 思路：nums2 是 nums1 每个元素加同一个整数 x 得到，元素大小关系不变，所以 x = min(nums2) - min(nums1)。
// 时间复杂度：O(n)，两次线性求最小值；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {  // nums1 是原数组，nums2 是每个元素都加上 x 之后的数组
        return *min_element(nums2.begin(), nums2.end()) - *min_element(nums1.begin(), nums1.end());  // 两组最小值同样相差 x，相减即得被加的整数（min_element 返回迭代器，需要解引用）
    }  // 方法体结束
};  // 类定义结束