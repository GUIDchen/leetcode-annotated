// 题目：1792. 最大平均通过率（Maximum Average Pass Ratio）
// 思路：贪心 + 大根堆：每多收一个学生，应分配给「通过率提升最大」的班级；堆里存当前增益，取堆顶加人后重算增益再入堆，最后求平均。
// 时间复杂度：O((n + extraStudents) log n)，每次堆操作 O(log n)；空间复杂度：O(n)，堆的大小等于班级数。
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {  // 主函数：把 extraStudents 个额外学生分配到各班级，使平均通过率最大
        priority_queue<tuple<double, int, int>> pq;  // 大根堆，元素为 (本次分配带来的增益, 已通过人数, 总人数)，堆顶增益最大
        for (auto& e : classes) {  // 先把每个班级的初始增益算出来入堆
            int a = e[0], b = e[1];  // 取出该班级的已通过人数 a 与总人数 b
            double x = (double) (a + 1) / (b + 1) - (double) a / b;  // 增益 = 多收 1 人后的通过率 - 当前通过率，用 double 避免整数除法
            pq.push({x, a, b});  // (增益, a, b) 入堆，等待被贪心选择
        }
        while (extraStudents--) {  // 每次循环分配一个学生，extraStudents 减到 0 为止
            auto [_, a, b] = pq.top();  // 取出增益最大的班级，下划线丢弃增益值
            pq.pop();  // 弹出该堆顶，稍后按新的增益重新入堆
            a++;  // 该班级多收 1 人：通过人数加一
            b++;  // 总人数也加一
            double x = (double) (a + 1) / (b + 1) - (double) a / b;  // 重新计算这个班级下一次加人带来的增益
            pq.push({x, a, b});  // 更新后的状态重新入堆
        }
        double ans = 0;  // 答案累加器：所有班级通过率之和
        while (pq.size()) {  // 把堆里剩余的班级全部取出，逐个累加通过率
            auto [_, a, b] = pq.top();  // 取出堆顶班级的三个字段
            pq.pop();  // 弹出，避免重复累加
            ans += (double) a / b;  // 累加该班级的通过率（浮点除法）
        }
        return ans / classes.size();  // 平均值 = 总通过率 / 班级数
    }  // 函数结束
};  // 题解类定义结束