// 题目：324. 摆动排序 II（Wiggle Sort II）
// 思路：先排序，再把「较小一半」从后往前填偶数下标、「较大一半」从后往前填奇数下标，使相邻元素严格交替。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，额外保存排序后的副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void wiggleSort(vector<int>& nums) {  // nums：待摆动排序的数组，要求原地修改
        vector<int> arr = nums;  // 先复制一份，排序时不破坏原数组（后面还要写回）
        sort(arr.begin(), arr.end());  // 升序排序，得到可以直接取到「较小一半」和「较大一半」的有序数组
        int n = nums.size();  // 数组长度
        int i = (n - 1) >> 1, j = n - 1;  // i 指向较小一半的末尾，j 指向较大一半的末尾
        for (int k = 0; k < n; ++k) {  // 按下标依次填充结果
            if (k % 2 == 0)  // 偶数下标放较小的一半
                nums[k] = arr[i--];  // 取较小一半的当前最大值，并让 i 左移
            else  // 奇数下标放较大的一半
                nums[k] = arr[j--];  // 取较大一半的当前最大值，并让 j 左移
        }  // 下标 k 的循环结束
    }  // 方法结束
};  // 类定义结束