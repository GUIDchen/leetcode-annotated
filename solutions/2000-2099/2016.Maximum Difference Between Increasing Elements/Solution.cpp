// 题目：2016. 增量元素之间的最大差值（Maximum Difference Between Increasing Elements）
// 思路：一次遍历，mi 维护已扫描部分的最小值；当前元素比 mi 大就用差值更新答案，否则把当前元素作为新的最小值。
// 时间复杂度：O(n)，只遍历一次；空间复杂度：O(1)，只用两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumDifference(vector<int>& nums) {  // nums：整数数组；返回满足 i < j 且 nums[i] < nums[j] 的最大差值，不存在则返回 -1
        int mi = 1 << 30;  // mi 保存已扫描元素的最小值，先取一个足够大的数（2^30）
        int ans = -1;  // ans 保存最大差值，初值 -1 表示「不存在」
        for (int& x : nums) {  // 按引用遍历每个元素，避免拷贝
            if (x > mi) {  // 当前元素严格大于之前的最小值，可构成合法数对
                ans = max(ans, x - mi);  // 用当前差值挑战已记录的最大差值
            } else {  // 否则当前元素不大于 mi
                mi = x;  // 当前元素更小（或相等），把它作为新的最小值，供后面比较
            }  // 分支结束
        }  // 循环结束
        return ans;  // 返回最大差值，可能为 -1
    }  // 方法结束
};  // 类定义结束