// 题目：1086. 前五科的均分（High Five）
// 思路：用下标为学号的数组收集每个学生的所有成绩，再按学号从小到大遍历：把该学生的成绩降序排序，取前 5 名求平均（整数除法），按学号顺序写入答案。
// 时间复杂度：O(n log n)，n 为成绩条数，瓶颈在各学生成绩的排序；空间复杂度：O(n)，用于存放按学号分组的所有成绩。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> highFive(vector<vector<int>>& items) {  // items 中每个元素是 [学号, 成绩]
        vector<int> d[1001];  // 下标 1~1000 对应学号，每个位置收集该学生的全部成绩（题目保证学号不超过 1000）
        for (auto& item : items) {  // 遍历每一条成绩记录（用引用避免拷贝）
            int i = item[0], x = item[1];  // i 是学号，x 是该次成绩
            d[i].push_back(x);  // 把成绩追加到对应学号的列表中
        }
        vector<vector<int>> ans;  // 存放 [学号, 前五科均分] 的结果，按学号升序
        for (int i = 1; i <= 1000; ++i) {  // 按学号从小到大扫描，天然得到题目要求的排序
            if (!d[i].empty()) {  // 该学号存在成绩记录才需要输出
                sort(d[i].begin(), d[i].end(), greater<int>());  // 按成绩从高到低排序，前 5 个即最高分
                int s = 0;  // 前五科成绩之和
                for (int j = 0; j < 5; ++j) {  // 取排序后的前 5 个成绩（题目保证每人至少 5 条记录）
                    s += d[i][j];  // 累加第 j 高的成绩
                }
                ans.push_back({i, s / 5});  // 整数除法求平均分，与学号一起写入答案
            }
        }
        return ans;  // 返回按学号升序排列的均分列表
    }
};