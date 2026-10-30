// 题目：167. 两数之和 II - 输入有序数组（Two Sum II - Input Array Is Sorted）
// 核心思路：利用数组有序，枚举第一个数，在它右侧用 lower_bound 二分查找补数 target - numbers[i]，命中即返回 1 基下标。
// 时间复杂度：O(n log n)，每个位置一次二分；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> twoSum(vector<int>& numbers, int target) {  // numbers：按非递减顺序排列的数组；target：目标和
        for (int i = 0, n = numbers.size();; ++i) {  // 枚举第一个数的下标 i；题目保证有解，故省略循环上界
            int x = target - numbers[i];  // 还需要的另一个数
            int j = lower_bound(numbers.begin() + i + 1, numbers.end(), x) - numbers.begin();  // 在 i 右侧区间二分查找 x 的插入位置（即第一个 >= x 的下标）
            if (j < n && numbers[j] == x) {  // lower_bound 不保证命中，还要确认下标合法且值真的等于 x
                return {i + 1, j + 1};  // 题目要求返回从 1 开始计数的两个下标
            }
        }  // 命中后一定会在循环内返回
    }
};