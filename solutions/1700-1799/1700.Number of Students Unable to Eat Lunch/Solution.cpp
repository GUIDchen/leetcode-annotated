// 题目：1700. 无法吃午餐的学生数量（Number of Students Unable to Eat Lunch）
// 思路：统计两种偏好的学生人数，再按栈顶顺序消耗；当栈顶类型已无人喜欢时，剩下的都是另一种偏好的学生。
// 时间复杂度：O(n + m)，n 为学生数、m 为三明治数；空间复杂度：O(1)，只用长度 2 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countStudents(vector<int>& students, vector<int>& sandwiches) {  // students：学生偏好队列；sandwiches：三明治栈
        int cnt[2] = {0};  // cnt[0]/cnt[1]：分别统计喜欢 0 型、1 型的学生人数
        for (int& v : students) ++cnt[v];  // 遍历学生，按偏好类型累加计数
        for (int& v : sandwiches) {  // 依次尝试发放栈顶的三明治
            if (cnt[v]-- == 0) {  // 先判断当前类型是否还有人要，再顺手把计数减一
                return cnt[v ^ 1];  // 无人喜欢该型，剩下的全是另一型偏好，v ^ 1 完成 0/1 互换
            }
        }
        return 0;  // 全部三明治都发出去了，所有人都吃到了
    }
};