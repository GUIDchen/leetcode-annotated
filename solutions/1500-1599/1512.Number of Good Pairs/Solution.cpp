// 题目：1512. 好数对的数目（Number of Good Pairs）
// 思路：一次遍历计数：当前元素与此前出现过的同值元素都构成好数对，把旧计数累加即可。
// 时间复杂度：O(n)，每个元素 O(1)；空间复杂度：O(1)，计数数组固定 101 个桶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numIdenticalPairs(vector<int>& nums) {  // nums：输入数组，返回满足 i<j 且 nums[i]==nums[j] 的下标对数
        int ans = 0;  // ans：累计的好数对数目
        int cnt[101]{};  // cnt[v]：值 v 已出现的次数，{} 表示全部初始化为 0；题目保证 1 <= nums[i] <= 100
        for (int& x : nums) {  // 用引用遍历，避免逐个元素拷贝
            ans += cnt[x]++;  // 后自增返回旧值：旧值即此前同值元素个数，也就是当前元素新增的好数对
        }  // 结束遍历
        return ans;  // 返回好数对总数
    }  // 结束方法
};  // 结束题解类