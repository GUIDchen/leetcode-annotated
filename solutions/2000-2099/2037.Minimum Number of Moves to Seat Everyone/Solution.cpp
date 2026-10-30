// 题目：2037. 使每位学生都有座位的最少移动次数（Minimum Number of Moves to Seat Everyone）
// 思路：排序后按位配对。座位与学生分别升序排序，第 i 小的座位配第 i 小的学生，总位移最小；答案为 ∑|seats[i] - students[i]|。
// 时间复杂度：O(n log n)，两次排序；空间复杂度：O(log n)，std::sort 的递归栈开销（原地排序）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {  // seats 是座位坐标，students 是学生初始位置，返回最少总移动次数
        sort(seats.begin(), seats.end());  // 座位升序排序
        sort(students.begin(), students.end());  // 学生位置升序排序
        int ans = 0;  // 累计总移动次数
        for (int i = 0; i < seats.size(); ++i) {  // 排序后按位配对，第 i 个学生去第 i 个座位
            ans += abs(seats[i] - students[i]);  // 两者距离即该学生需要的移动步数
        }  // 结束累加循环
        return ans;  // 返回最少移动次数
    }  // 结束 minMovesToSeat
};  // 结束 Solution 类