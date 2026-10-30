// 题目：3450. 一张长椅上的最多学生（Maximum Students on a Single Bench）
// 思路：同一张长椅上可能有多条记录，同一个学生也可能被重复记录，所以用「长椅编号 -> 学生编号集合」的哈希表聚拢数据，集合天然去重；最后遍历每张长椅，取集合大小的最大值。
// 时间复杂度：O(n)，每条记录只做一次哈希插入；空间复杂度：O(n)，最坏情况下存下所有记录。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxStudentsOnBench(vector<vector<int>>& students) {  // students：每条记录是 [student_id, bench_id]；返回单张长椅上的最多学生数
        unordered_map<int, unordered_set<int>> d;  // d：长椅编号 -> 坐在这张长椅上的学生集合（自动去重）
        for (const auto& e : students) {  // 遍历每条学生与长椅的记录
            int studentId = e[0], benchId = e[1];  // e[0] 是学生编号，e[1] 是长椅编号
            d[benchId].insert(studentId);  // 把学生放进对应长椅的集合，重复插入不会生效
        }
        int ans = 0;  // ans 记录单张长椅上最多的学生人数
        for (const auto& s : d) {  // 遍历每张至少坐了一个学生的长椅
            ans = max(ans, (int) s.second.size());  // s.second 是学生集合，用它的规模更新最优解
        }
        return ans;  // 返回人数最多的长椅上的学生数，没有任何记录时返回 0
    }  // 方法结束
};  // 类定义结束
