// 题目：2600. K 件物品的最大和（K Items With the Maximum Sum）
// 思路：贪心先拿价值最高的 1，再拿 0，最后才拿 -1，三段按剩余件数依次结算即可。
// 时间复杂度：O(1)，只有常数次比较；空间复杂度：O(1)，只用几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {  // numOnes/numZeros/numNegOnes 分别是 1、0、-1 的个数，k 是要取的件数
        if (numOnes >= k) {  // 情况一：1 足够多，全部取 1，和就是 k
            return k;  // 直接返回每件都取 1 的和
        }  // 情况二：1 不够、但加上 0 后够 k 件，剩下的都用 0 补
        if (numZeros >= k - numOnes) {  // 0 不改变和，答案就是所有 1 的和
            return numOnes;  // 情况三：1 和 0 都不够，剩余件数只能取 -1，每件减一
        }  // 方法体结束，返回最大和
        return numOnes - (k - numOnes - numZeros);
    }
};