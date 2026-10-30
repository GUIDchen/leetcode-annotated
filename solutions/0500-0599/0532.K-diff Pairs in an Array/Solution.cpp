// 题目：532. 数组中的 k-diff 数对（K-diff Pairs in an Array）
// 思路：边遍历边用哈希集合 vis 记录见过的值，用集合 ans 去重；每个数只看「更小的伙伴」是否已出现，天然不重复。
// 时间复杂度：O(n)，每个元素只做常数次哈希操作；空间复杂度：O(n)，两个集合最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int findPairs(vector<int>& nums, int k) {  // nums 是输入数组，k 是要求的绝对差
        unordered_set<int> ans, vis;  // ans 存数对里较小的那个值（自动去重）；vis 存已经遍历过的值
        for (int x : nums) {  // 按顺序遍历每个元素
            if (vis.count(x - k)) {  // 比 x 小 k 的伙伴之前出现过，则 (x-k, x) 构成合法数对
                ans.insert(x - k);  // 用较小的值 x-k 代表这个数对，重复出现也只记一次
            }
            if (vis.count(x + k)) {  // 比 x 大 k 的伙伴之前出现过，则 (x, x+k) 构成合法数对
                ans.insert(x);  // 同样用较小的值 x 代表这个数对
            }
            vis.insert(x);  // 把当前值加入已见集合，供后面的元素配对；放在最后，避免 k=0 时自己和自己配对
        }
        return ans.size();  // 集合大小就是不同数对的个数
    }
};
