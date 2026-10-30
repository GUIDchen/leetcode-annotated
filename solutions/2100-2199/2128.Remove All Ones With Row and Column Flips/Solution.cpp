// 题目：2128. 通过翻转行或列来去除所有的 1（Remove All Ones With Row and Column Flips）
// 核心思路：翻列只会整列取反。把每行按「首元素」归一化成首列为 0 的形态，若所有行归一化后完全一致，就能靠翻列再翻行清掉所有 1。
// 时间复杂度：O(m·n)，每格处理一次；空间复杂度：O(m·n)，集合里保存每行的归一化字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool removeOnes(vector<vector<int>>& grid) {  // grid 是只含 0/1 的矩阵；返回能否通过翻整行或整列把所有 1 变成 0
        unordered_set<string> s;  // 集合用来收集每行归一化后的样子，重复的会自然去重
        for (auto& row : grid) {  // 逐行处理
            string t;  // t 存放本行归一化后的字符串
            for (int x : row) {  // 逐列读取本行的每个元素
                t.push_back('0' + (row[0] == 0 ? x : x ^ 1));  // 首元素是 0 就保留原值，否则整行取反（x ^ 1）；再 + '0' 转成字符
            }
            s.insert(t);  // 归一化结果放进集合，等价的行只保留一份
        }
        return s.size() == 1;  // 集合大小为 1 说明所有行归一化后相同，可以先按需翻列、再翻行清掉所有的 1
    }
};