// 题目：1170. 比较字符串最小字母出现频次（Compare Strings by Frequency of the Smallest Character）
// 思路：先算出每个单词的 f 值并排序，再对每个查询串算 f 值，用二分（upper_bound）数出单词中 f 值严格更大的个数。
// 时间复杂度：O(|words|·L + |words| log |words| + |queries|·L log |words|)；空间复杂度：O(|words|)。
class Solution {  // 题解类
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {  // 对每个查询串，统计有多少个单词的 f 值严格大于它的 f 值
        auto f = [](string s) {  // 匿名函数 f：求题目定义的「最小字母的出现频次」
            int cnt[26] = {0};  // 26 个小写字母的计数数组，初始化为 0
            for (char c : s) {  // 遍历字符串中的每个字符
                cnt[c - 'a']++;  // 对应字母的计数加一
            }  // for 结束
            for (int x : cnt) {  // 按字母从小到大找第一个出现过的字母
                if (x) {  // 计数不为 0 说明找到了当前最小字母
                    return x;  // 返回它的出现频次
                }  // if 结束
            }  // for 结束
            return 0;  // 空串兜底返回 0（题目保证非空）
        };  // lambda 定义结束
        int n = words.size();  // 单词个数
        int nums[n];  // 保存每个单词的 f 值
        for (int i = 0; i < n; i++) {  // 逐个计算单词的 f 值
            nums[i] = f(words[i]);  // 存入数组
        }  // for 结束
        sort(nums, nums + n);  // 排序，方便后面二分查找
        vector<int> ans;  // 存放答案
        for (auto& q : queries) {  // 逐个处理查询串
            int x = f(q);  // 计算查询串的 f 值
            ans.push_back(n - (upper_bound(nums, nums + n, x) - nums));  // 排序后严格大于 x 的个数 = n 减去第一个大于 x 的下标
        }  // for 结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束