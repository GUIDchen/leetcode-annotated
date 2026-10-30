// 题目：3085. 成为 K 特殊字符串需要删除的最少字符数（Minimum Deletions to Make String K-Special）
// 思路：统计各字符频次，枚举保留下来的最小频次 v；低于 v 的字符整类删除，高于 v + k 的削到 v + k，取总删除数最小者。
// 时间复杂度：O(n·26)，n 为字符串长度，枚举 n+1 个下界、每个下界扫一遍至多 26 个频次；空间复杂度：O(1)，只用了 26 个计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDeletions(string word, int k) {  // word 为输入字符串，k 为任意两个出现过的字符频次之差的上限
        int freq[26]{};  // 统计 26 个小写字母的出现次数，{} 让数组全部初始化为 0
        for (char& c : word) {  // 遍历字符串中的每个字符（用引用避免拷贝）
            ++freq[c - 'a'];  // 把字符映射成 0..25 的下标，对应频次加一
        }
        vector<int> nums;  // nums 存放「出现过」的字符频次，零频次不参与计算
        for (int v : freq) {  // 遍历 26 个字母的频次
            if (v) {  // 只保留出现过的字符
                nums.push_back(v);  // 收集该字符的频次
            }
        }
        int n = word.size();  // 字符串长度，也是删除总数的上界
        int ans = n;  // 先以「把字符全删光」作为可行答案的初值
        auto f = [&](int v) {  // lambda f(v)：以 v 为保留下来的最小频次，返回该方案的总删除数
            int ans = 0;  // 本次枚举的删除数（与外层 ans 同名，但作用域只在 lambda 内）
            for (int x : nums) {  // 逐个检查每种字符的频次 x
                if (x < v) {  // 频次低于下界 v，这类字符无法保留
                    ans += x;  // 整类删除，代价为它的全部出现次数
                } else if (x > v + k) {  // 频次高于上界 v + k，只能保留 v + k 个
                    ans += x - v - k;  // 删掉超出的 x - (v + k) 个字符
                }
            }
            return ans;  // 返回该下界下的删除总数
        };  // lambda 定义结束
        for (int i = 0; i <= n; ++i) {  // 枚举所有可能的下界（循环变量 i 即下界 v，范围 0..n）
            ans = min(ans, f(i));  // 在所有下界中取最小删除数
        }
        return ans;  // 返回最优答案
    }
};  // 类定义结束