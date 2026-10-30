// 题目：1460. 通过翻转子数组使两个数组相等（Make Two Arrays Equal by Reversing Subarrays）
// 思路：反转任意子数组只改变顺序、不改变元素的多重集合，所以两数组可互相转化当且仅当排序后完全相同。
// 时间复杂度：O(n log n)，排序是主要开销；空间复杂度：O(log n)，std::sort 的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canBeEqual(vector<int>& target, vector<int>& arr) {  // target、arr：两个待比较的数组
        sort(target.begin(), target.end());  // 把 target 升序排序，抹掉顺序上的差异
        sort(arr.begin(), arr.end());  // 把 arr 同样升序排序
        return target == arr;  // 排序后逐位相同，说明元素集合一致，可以通过翻转互相得到
    }  // 方法体结束
};  // 类定义结束