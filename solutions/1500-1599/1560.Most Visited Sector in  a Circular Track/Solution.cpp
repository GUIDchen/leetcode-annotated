// 题目：1560. 圆形赛道上经过次数最多的扇区（Most Visited Sector in a Circular Track）
// 思路：每一轮的路径都是环上的连续一段，只有最后一段会与其他段重叠；因此经过次数最多的扇区就是最后一段覆盖的扇区（若跨过 n→1 边界则拆成两段）。
// 时间复杂度：O(n)，最多输出 n 个扇区；空间复杂度：O(n)，用于存放答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> mostVisited(int n, vector<int>& rounds) {  // n：扇区总数；rounds：每轮的起始扇区，相邻两项表示一轮
        int m = rounds.size() - 1;  // m 是最后一轮的起始下标，rounds[m] 是整场比赛的终点
        vector<int> ans;  // 保存经过次数最多的扇区编号
        if (rounds[0] <= rounds[m]) {  // 起点编号不大于终点，说明最后一段没有跨过 n → 1 的边界
            for (int i = rounds[0]; i <= rounds[m]; ++i) {  // 最后一段 [起点, 终点] 被多走一次，正是经过次数最多的扇区
                ans.push_back(i);  // 逐个收进答案
            }  // 循环体结束
        } else {  // 否则最后一段跨过了边界，被多走的区间是 [1, 终点] ∪ [起点, n]
            for (int i = 1; i <= rounds[m]; ++i) {  // 先收 [1, 终点] 这一段
                ans.push_back(i);  // 逐个收进答案
            }  // 循环体结束
            for (int i = rounds[0]; i <= n; ++i) {  // 再收 [起点, n] 这一段
                ans.push_back(i);  // 逐个收进答案
            }  // 循环体结束
        }  // 分支结束
        return ans;  // 返回按编号升序排列的答案
    }  // 方法结束
};  // 类定义结束
