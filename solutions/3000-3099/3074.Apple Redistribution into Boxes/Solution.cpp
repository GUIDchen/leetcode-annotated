// 题目：3074. 重新分装苹果（Apple Redistribution into Boxes）
// 思路：贪心。苹果总数固定，优先用容量最大的箱子，按容量降序累减，剩余苹果数首次不超过 0 时的箱子数就是答案。
// 时间复杂度：O(m log m + n)，排序加求苹果总和；空间复杂度：O(1)，排序在原数组上进行。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {  // apple：每个包裹的苹果数；capacity：每个箱子的容量；返回最少需要选用的箱子数
        sort(capacity.rbegin(), capacity.rend());  // 容量从大到小排序，保证贪心时总是先拿最大的箱子
        int s = accumulate(apple.begin(), apple.end(), 0);  // 苹果总数，即需要装箱的苹果总量
        for (int i = 1;; ++i) {  // i 表示当前选用的箱子数，从 1 开始无限递增（题目保证一定装得下）
            s -= capacity[i - 1];  // 用掉第 i 个（容量第 i 大）的箱子
            if (s <= 0) {  // 剩余苹果不超过 0，说明这 i 个箱子已经能装下全部苹果
                return i;  // 箱子数最少，直接返回 i
            }
        }
    }
};