// 题目：1481. 不同整数的最少数目（Least Number of Unique Integers after K Removals）
// 思路：先统计每个数的出现次数，把次数排序；为了让剩下的不同整数最少，优先删掉出现次数最少的数，能删几个就少几个不同整数。
// 时间复杂度：O(n + u log u)，u 为不同整数个数；空间复杂度：O(u)，哈希表与频次数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {  // arr：输入数组；k：最多可删除的元素个数
        unordered_map<int, int> cnt;  // 哈希表：键是元素值，值是它的出现次数
        for (int& x : arr) {  // 遍历数组，统计每个元素的频次
            ++cnt[x];  // 当前元素的计数加一
        }
        vector<int> nums;  // 用来存放所有出现次数
        for (auto& [_, c] : cnt) {  // 结构化绑定遍历哈希表（_ 是键，c 是次数）
            nums.push_back(c);  // 只收集次数，键本身已经用不到了
        }
        sort(nums.begin(), nums.end());  // 次数从小到大排序，才能优先删除代价最小的数
        for (int i = 0, m = nums.size(); i < m; ++i) {  // i 为已删除的「不同整数」个数，m 为不同整数总数
            k -= nums[i];  // 尝试把这个数整个删掉，消耗它的全部出现次数
            if (k < 0) {  // 次数不够，说明这个数只能删一部分、仍然存在
                return m - i;  // 前 i 个已彻底删掉，剩下的不同整数个数为 m - i
            }
        }
        return 0;  // k 足够删光所有数，不同整数个数为 0
    }
};