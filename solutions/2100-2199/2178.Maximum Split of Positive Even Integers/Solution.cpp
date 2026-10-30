// 题目：2178. 拆分成最多数目的正偶数之和（Maximum Split of Positive Even Integers）
// 思路：贪心地从 2 开始依次加入 2、4、6…；当剩余值不足下一个偶数时，把余量并入最后一个偶数，个数即为最多。
// 时间复杂度：O(√n)，最多累加约 √n 个偶数；空间复杂度：O(√n)，答案数组的长度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> maximumEvenSplit(long long finalSum) {  // finalSum：需要拆分的正偶数之和
        vector<long long> ans;  // 存放拆分出的各个偶数（从 2 开始依次递增）
        if (finalSum % 2) {  // 奇数不可能拆成若干个偶数之和，直接返回空方案
            return ans;  // 无解时返回空的拆分方案
        }
        for (long long i = 2; i <= finalSum; i += 2) {  // 贪心：每次取当前最小的偶数，保证拆出的个数最多
            ans.push_back(i);  // 把当前偶数加入方案
            finalSum -= i;  // 剩余待分配的和减少 i
        }
        ans.back() += finalSum;  // 余量并入最后一个偶数，总和不变且各数仍互不相同
        return ans;  // 返回数目最多的拆分方案
    }
};  // 类定义结束
