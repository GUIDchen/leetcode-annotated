// 题目：2512. 奖励最顶尖的 K 名学生（Reward Top K Students）
// 思路：把正面/负面评语分别放进哈希集合，逐个学生按空格拆词算总分（正面 +3、负面 -1），再按「分数降序、学号升序」排序取前 k 个学号。
// 时间复杂度：O(R·L + R log R)，R 为学生数、L 为每条评语的单词数；空间复杂度：O(R + P + N)，即结果数组与两个词表集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {  // 依次是正面词、负面词、评语、学号，k 为奖励人数
        unordered_set<string> ps(positive_feedback.begin(), positive_feedback.end());  // 正面词哈希集合，判断某词是否加分是 O(1)
        unordered_set<string> ns(negative_feedback.begin(), negative_feedback.end());  // 负面词哈希集合，判断某词是否扣分是 O(1)
        vector<pair<int, int>> arr;  // 存 (负分数, 学号)，这样 pair 默认升序排序恰好是「分数降序」
        int n = report.size();  // 学生人数
        for (int i = 0; i < n; ++i) {  // 逐个学生计算总分
            int sid = student_id[i];  // 当前学生的学号
            vector<string> ws = split(report[i], ' ');  // 按空格把评语拆成单词（题面保证单词间只有一个空格）
            int t = 0;  // 当前学生的得分
            for (auto& w : ws) {  // 遍历这条评语里的每个单词
                if (ps.count(w)) {  // 该词出现在正面评语中
                    t += 3;  // 正面评语加 3 分
                } else if (ns.count(w)) {  // 否则再看是否为负面评语
                    t -= 1;  // 负面评语扣 1 分
                }
            }
            arr.push_back({-t, sid});  // 存负分数让高分靠前；同分时学号小的靠前
        }
        sort(arr.begin(), arr.end());  // 先按分数降序（-t 升序），分数相同时按学号升序
        vector<int> ans;  // 保存答案学号
        for (int i = 0; i < k; ++i) {  // 取排序后的前 k 名学生
            ans.emplace_back(arr[i].second);  // 取出该学生的学号
        }
        return ans;  // 按名次返回最顶尖的 k 个学号
    }

    vector<string> split(string& s, char delim) {  // 辅助函数：按分隔符把字符串切成若干片段
        stringstream ss(s);  // 把字符串包装成输入流
        string item;  // 暂存每次读出的片段
        vector<string> res;  // 存放切分结果
        while (getline(ss, item, delim)) {  // 一直读到分隔符或流末尾
            res.emplace_back(item);  // 把读到的片段加入结果
        }
        return res;  // 返回切分好的单词列表
    }
};