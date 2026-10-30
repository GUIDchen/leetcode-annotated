// 题目：630. 课程表 III（Course Schedule III）
// 思路：按截止时间升序排序后贪心：能塞进截止时间就选，塞不下就丢掉已选课程里时长最长的那一门，用大顶堆维护已选时长。
// 时间复杂度：O(n log n)，排序加每门课一次堆操作；空间复杂度：O(n)，堆中最多 n 个时长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int scheduleCourse(vector<vector<int>>& courses) {  // courses[i] = [duration, lastDay]，返回最多能修的课程门数
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {  // 按截止时间升序排序：先到期的课优先占时间，这是贪心的前提
            return a[1] < b[1];  // 比较函数只看第二个元素，即截止时间 lastDay
        });  // 排序调用结束
        priority_queue<int> pq;  // 大顶堆：保存已选课程的时长，堆顶是当前选中的最长课程
        int s = 0;  // s 是已选课程的总时长，也就是当前时间（从 0 时刻开始）
        for (auto& e : courses) {  // 按截止时间从早到晚，逐门决定是否选课
            int duration = e[0], last = e[1];  // 取出该课的时长与截止时间
            pq.push(duration);  // 先假设选上这门课，把它压入堆
            s += duration;  // 总时长随之增加
            while (s > last) {  // 总时长超过当前课截止时间就必须淘汰一门课
                s -= pq.top();  // 淘汰已选课程中时长最长的一门，使总时长下降最多
                pq.pop();  // 把它从堆中弹出
            }  // 淘汰循环结束
        }  // 所有课程遍历结束
        return pq.size();  // 堆中剩下的课程数就是最多能修的课程数
    }  // 方法结束
};  // 类定义结束