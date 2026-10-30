// 题目：2091. 从数组中移除最大值和最小值（Removing Minimum and Maximum From Array）
// 思路：先一次遍历定位最小值与最大值下标（设小者在左、大者在右），再比较三种删法：都从左边删、都从右边删、小的从左边删且大的从右边删，取次数最少者。
// 时间复杂度：O(n)，只需一次遍历加常数次比较；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDeletions(vector<int>& nums) {  // nums：原数组；返回删掉最大值和最小值所需的最少操作次数
        int mi = 0, mx = 0, n = nums.size();  // mi/mx 记录最小值、最大值的下标（初值都指向 0 号元素），n 为数组长度
        for (int i = 0; i < n; ++i) {  // 一次遍历同时找最大值与最小值的位置
            if (nums[i] < nums[mi]) mi = i;  // 发现更小的值，更新最小值下标
            if (nums[i] > nums[mx]) mx = i;  // 发现更大的值，更新最大值下标（两行 if 互相独立，不能写成 else if）
        }  // 遍历结束
        if (mi > mx) {  // 保证 mi 是较左的下标、mx 是较右的下标，方便后面统一表述
            int t = mi;  // 用临时变量 t 交换两个下标
            mi = mx;  // mi 改为较小的下标
            mx = t;  // mx 改为较大的下标
        }  // 交换分支结束
        return min(min(mx + 1, n - mi), mi + 1 + n - mx);  // 三种删法取最小：①都从左边删需 mx+1 次；②都从右边删需 n-mi 次；③小的从左边删、大的从右边删需 mi+1+n-mx 次
    }  // 结束 minimumDeletions 方法
};  // 结束 Solution 类