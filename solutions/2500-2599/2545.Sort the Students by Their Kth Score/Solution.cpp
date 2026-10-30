// 题目：2545. 根据第 K 场考试的分数排序（Sort the Students by Their Kth Score）
// 思路：直接按每个学生第 k 列的成绩降序排序整行。
// 时间复杂度：O(m log m)，m 为学生人数；空间复杂度：O(log m)，排序的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) {  // score 每行是一个学生的各科成绩，k 是排序依据的列下标
        ranges::sort(score, [k](const auto& a, const auto& b) { return a[k] > b[k]; });  // C++20 的 ranges::sort，比较器按第 k 列从大到小（>）排序
        return score;  // 返回排序后的二维数组
    }  // 方法结束
};  // 类定义结束
