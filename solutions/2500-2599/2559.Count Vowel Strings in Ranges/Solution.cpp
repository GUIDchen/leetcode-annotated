// 题目：2559. 统计范围内的元音字符串数（Count Vowel Strings in Ranges）
// 核心思路：把「首尾都是元音」的单词下标记入有序数组，再用二分回答每个查询区间内有多少个这样的下标。
// 时间复杂度：O(n + q log n)，n 为单词数、q 为查询数；空间复杂度：O(n)，用于保存有序下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {  // words：单词表；queries：若干闭区间 [l, r]
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};  // 元音集合，用哈希实现 O(1) 判定
        vector<int> nums;  // 记录「首尾都是元音」的单词下标，插入顺序天然递增
        for (int i = 0; i < words.size(); ++i) {  // 从左到右扫描每个单词
            char a = words[i][0], b = words[i].back();  // a 是首字母；b 是尾字母（back() 取最后一个字符）
            if (vowels.count(a) && vowels.count(b)) {  // 首字母与尾字母都在元音集合中
                nums.push_back(i);  // 该下标满足条件，收集起来供后续二分使用
            }
        }
        vector<int> ans;  // 按查询顺序存放每个答案
        for (auto& q : queries) {  // 逐个处理查询区间
            int l = q[0], r = q[1];  // 本次查询的左、右端点
            int cnt = upper_bound(nums.begin(), nums.end(), r) - lower_bound(nums.begin(), nums.end(), l);  // [l, r] 内的下标数 = 第一个大于 r 的位置 - 第一个大于等于 l 的位置
            ans.push_back(cnt);  // 记录本次查询的结果
        }
        return ans;  // 返回全部查询的答案
    }
};