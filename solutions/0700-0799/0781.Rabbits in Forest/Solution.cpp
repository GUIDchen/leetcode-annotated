// 题目：781. 森林中的兔子（Rabbits in Forest）
// 思路：若某只兔子回答 x，说明与它同色的兔子共有 x+1 只（含自己）。统计每个答案 x 的出现次数 v，这 v 只兔子至少要被分成 ceil(v/(x+1)) 个大小为 x+1 的组，该答案贡献的兔子数就是组数乘以组大小。
// 时间复杂度：O(n)，遍历一次数组和一次哈希表；空间复杂度：O(n)，哈希表最多存 n 个不同的答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numRabbits(vector<int>& answers) {  // answers：每只兔子的回答；返回森林中最少可能的兔子总数
        unordered_map<int, int> cnt;  // 哈希表：键是回答 x，值是回答 x 的兔子数量
        for (int x : answers) {  // 遍历每只兔子的回答
            ++cnt[x];  // 对应答案的计数加一
        }
        int ans = 0;  // ans：统计出的最少兔子总数
        for (auto& [x, v] : cnt) {  // 结构化绑定遍历哈希表：x 是答案，v 是回答 x 的兔子个数
            int group = x + 1;  // 同色兔子的组大小固定为 x+1（因为回答 x 意味着还有 x 个同色伙伴）
            ans += (v + group - 1) / group * group;  // (v+group-1)/group 是向上取整的组数，乘以 group 得到这批兔子至少要占的名额
        }
        return ans;  // 返回最少兔子总数
    }  // numRabbits 方法结束
};  // Solution 类定义结束
