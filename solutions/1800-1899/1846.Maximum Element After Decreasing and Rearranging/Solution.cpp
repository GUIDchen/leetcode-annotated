// 题目：1846. 减小和重新排列数组后的最大元素（Maximum Element After Decreasing and Rearranging）
// 思路：先排序，把首元素压到 1，再从左到右令 arr[i] = min(arr[i], arr[i-1]+1)，这样每步都取可行上限，末元素即为答案。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(log n)，排序递归栈（原地修改传入数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {  // arr：可任意重排、只能减小的数组
        ranges::sort(arr);  // 排序后小值在前，便于逐个把相邻差压到不超过 1
        int n = arr.size();  // 数组长度
        arr[0] = 1;  // 条件要求首元素必须等于 1，直接改小即可（减小合法）
        for (int i = 1; i < n; ++i) {  // 从第二项开始向右推进
            arr[i] = min(arr[i], arr[i - 1] + 1);  // 相邻差最多为 1，取"原值"与"前项+1"的较小者
        }

        return arr[n - 1];  // 末元素已经是在这些约束下能取到的最大值
    }
};