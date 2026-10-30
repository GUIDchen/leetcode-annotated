// 题目：2344. 使数组可以被整除的最少删除次数（Minimum Deletions to Make Array Divisible）
// 思路：先求出 numsDivide 所有元素的最大公约数 x，再把 nums 升序排序，第一个能整除 x 的元素下标就是最少删除次数。
// 时间复杂度：O(m log C + n log n)，m、n 为两数组长度，log C 为求 gcd 的对数代价；空间复杂度：O(log n)（排序递归栈）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {  // nums：可删除元素的数组；numsDivide：要求每个元素都被整除的数组
        int x = 0;  // gcd 的累加器，初值取 0：0 与任何数的 gcd 都等于该数本身
        for (int& v : numsDivide) {  // 遍历 numsDivide 的每个元素
            x = gcd(x, v);  // 把当前公共 gcd 与 v 再求一次 gcd，逐步合并成整体 gcd
        }
        sort(nums.begin(), nums.end());  // 升序排序：越小的数越可能整除 x，第一次命中即为最少删除
        for (int i = 0; i < nums.size(); ++i) {  // 从最小的数开始逐个检查
            if (x % nums[i] == 0) {  // 该数能整除 x（x 是 numsDivide 的公约数），因此它也能整除 numsDivide 的所有元素
                return i;  // 它左边形如更小但不能整除的元素必须全部删掉，共 i 个，答案即 i
            }
        }
        return -1;  // 没有任何元素能整除 x，无法使 numsDivide 被整除，返回 -1
    }
};