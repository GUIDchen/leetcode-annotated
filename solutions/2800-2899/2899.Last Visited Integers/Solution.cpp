// 题目：2899. 上一个遍历的整数（Last Visited Integers）
// 思路：按出现顺序记录遇到的正整数；每遇到一个 -1 就把连续计数 k 加一，再取倒数第 k 个记录，不足则记 -1；遇到正整数时把 k 清零。
// 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，seen 最多存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> lastVisitedIntegers(vector<int>& nums) {  // nums：由正整数与 -1 组成的数组
        vector<int> seen;  // seen：按出现顺序保存遇到的正整数
        vector<int> ans;  // ans：保存每个 -1 对应的答案
        int k = 0;  // k：当前连续出现的 -1 的个数

        for (int x : nums) {  // 从左到右扫描数组
            if (x == -1) {  // 遇到 -1，表示要回溯访问
                if (++k > seen.size()) {  // 先把连续计数加一，再看历史记录是否够用
                    ans.push_back(-1);  // 记录不够，没有可回溯的数，答案记 -1
                } else {  // 历史记录够用
                    ans.push_back(seen[seen.size() - k]);  // 取倒数第 k 个出现过的正整数
                }
            } else {  // 遇到正整数
                k = 0;  // 连续 -1 的计数清零
                seen.push_back(x);  // 把这个数追加到历史记录末尾
            }
        }

        return ans;  // 返回所有 -1 的答案
    }
};
