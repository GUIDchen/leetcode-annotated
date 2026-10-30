// 题目：274. H 指数（H-Index）
// 思路：把引用次数降序排序，然后从 n 向下枚举 h，第一个满足 citations[h-1] >= h 的 h 就是最大 H 指数。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，原地排序。
class Solution {  // LeetCode 约定的题解类
public:  // 对外提供 hIndex 方法
    int hIndex(vector<int>& citations) {  // citations：每篇论文的引用次数
        sort(citations.rbegin(), citations.rend());  // 先降序排序，方便用下标判断「至少有 h 篇引用数 ≥ h」
        for (int h = citations.size(); h; --h) {  // h 从 n 递减到 1；h 为 0 时条件为假，循环自然结束
            if (citations[h - 1] >= h) {  // 降序后 citations[h-1] 是前 h 篇里引用最少的一篇
                return h;  // 满足条件，h 就是最大的 H 指数
            }
        }
        return 0;  // 都不满足说明 H 指数为 0
    }
};