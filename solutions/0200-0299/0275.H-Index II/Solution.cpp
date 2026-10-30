// 题目：275. H 指数 II（H-Index II）
// 思路：citations 已升序，H 指数满足单调性，于是二分答案 mid，用 citations[n-mid] >= mid 判断 mid 是否可行，不断收缩区间取最大可行值。
// 时间复杂度：O(log n)，二分答案；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外提供 hIndex 方法
    int hIndex(vector<int>& citations) {  // citations：非递减排序的引用次数数组
        int n = citations.size();  // n：论文篇数
        int left = 0, right = n;  // 二分区间 [left, right]，H 指数的取值范围是 0..n
        while (left < right) {  // 区间没收缩完就继续二分
            int mid = (left + right + 1) >> 1;  // 取上中位数，配合下面 left = mid 才不会死循环
            if (citations[n - mid] >= mid)  // citations[n-mid] 是倒数第 mid 篇，它 ≥ mid 说明答案是可行的
                left = mid;  // mid 可行，尝试更大的答案
            else  // 否则 mid 不可行
                right = mid - 1;  // 答案必然更小，收缩右边界
        }
        return left;  // left == right 时就是最大可行的 H 指数
    }
};