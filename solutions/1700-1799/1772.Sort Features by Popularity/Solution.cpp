// 题目：1772. 按受欢迎程度排列功能（Sort Features by Popularity）
// 思路：先统计每个功能被多少个不同用户提到（同一反馈内单词先去重），再对下标排序，热度降序且热度相同时保持输入顺序。
// 时间复杂度：O(m·L + n log n)，m 为反馈条数、L 为单条反馈长度、n 为功能数；空间复杂度：O(m·L) 用于存词频。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> sortFeatures(vector<string>& features, vector<string>& responses) {  // features：待排序的功能名；responses：每个用户的反馈句子
        unordered_map<string, int> cnt;  // 统计每个功能被多少个不同的用户提到
        for (auto& s : responses) {  // 逐条处理每个用户的反馈句子
            istringstream iss(s);  // 用字符串流把句子按空格拆成单词
            string w;  // 存放当前读出的单词
            unordered_set<string> st;  // 同一条反馈内去重，保证一个用户只计一次
            while (iss >> w) {  // 不断读词，直到句子读完
                st.insert(w);  // 放入集合，重复单词自动忽略
            }
            for (auto& w : st) {  // 遍历这条反馈去重后的单词
                ++cnt[w];  // 该功能的提及用户数加一
            }
        }
        int n = features.size();  // 功能个数
        vector<int> idx(n);  // 存放下标，稍后按热度对下标排序
        iota(idx.begin(), idx.end(), 0);  // 用 0..n-1 依次填充下标数组
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按热度降序排序下标；热度相同则保持原有先后顺序
            int x = cnt[features[i]], y = cnt[features[j]];  // 取出两个功能各自的热度
            return x == y ? i < j : x > y;  // 热度相同就比下标（保证稳定），否则热度高的排前面
        });
        vector<string> ans(n);  // 存放最终的排序结果
        for (int i = 0; i < n; ++i) {  // 按排名顺序逐个填入功能名
            ans[i] = features[idx[i]];  // 第 i 位放热度排名第 i 的功能
        }
        return ans;  // 返回按热度排列的功能名列表
    }
};  // 类定义结束