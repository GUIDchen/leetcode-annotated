// 题目：1574. 删除最短的子数组使剩余数组有序（Shortest Subarray to be Removed to Make Array Sorted）
// 思路：先求出最长非递减前缀终点 i 与最长非递减后缀起点 j；答案先取只保留一侧的代价，再枚举前缀末尾 l，在后缀里二分出第一个不小于 arr[l] 的位置 r，删除区间 (l, r) 得到候选答案。
// 时间复杂度：O(n log n)，枚举前缀 O(n) 次、每次二分 O(log n)；空间复杂度：O(1)，只用常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findLengthOfShortestSubarray(vector<int>& arr) {  // arr：输入的整数数组，返回需要删除的最短子数组长度
        int n = arr.size();  // 数组长度，后面所有下标边界判断都基于它
        int i = 0, j = n - 1;  // i 指向最长非递减前缀的末位，j 指向最长非递减后缀的首位
        while (i + 1 < n && arr[i] <= arr[i + 1]) {  // 只要右侧邻居不小于自己，前缀就还能继续向右延伸
            ++i;  // 前缀右扩一位
        }  // while 循环结束
        while (j - 1 >= 0 && arr[j - 1] <= arr[j]) {  // 只要左侧邻居不大于自己，后缀就还能继续向左延伸
            --j;  // 后缀左扩一位
        }  // while 循环结束
        if (i >= j) {  // 前后缀区间已经重叠或相邻，说明整个数组本来就非递减
            return 0;  // 无需删除任何元素
        }  // if 分支结束
        int ans = min(n - 1 - i, j);  // 两种只保留一侧的方案：删掉 i 之后的全部，或删掉 j 之前的全部，取较小者
        for (int l = 0; l <= i; ++l) {  // 枚举保留下来的前缀末尾位置 l（0..i）
            int r = lower_bound(arr.begin() + j, arr.end(), arr[l]) - arr.begin();  // 在有序后缀 j..n-1 中二分出第一个 >= arr[l] 的下标 r
            ans = min(ans, r - l - 1);  // 删掉开区间 (l, r) 内的元素即可让两段拼接后有序，长度为 r-l-1
        }  // for 循环结束
        return ans;  // 返回最短删除长度
    }  // 方法结束
};  // 题解类结束