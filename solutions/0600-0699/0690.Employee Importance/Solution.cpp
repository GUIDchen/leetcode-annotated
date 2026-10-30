// 题目：690. 员工的重要性（Employee Importance）
// 思路：先用哈希表建立「员工 id → 员工对象」的索引，再从给定 id 出发 DFS 累加重要度并递归所有下属。
// 时间复杂度：O(n)，每个员工只被访问一次；空间复杂度：O(n)，哈希表与递归栈。
/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getImportance(vector<Employee*> employees, int id) {  // employees 是全体员工，id 是查询起点，返回该员工及其所有下属的重要度之和
        unordered_map<int, Employee*> d;  // 哈希表：键是员工 id，值是员工对象指针，便于 O(1) 按 id 查找
        for (auto& e : employees) {  // 遍历员工列表，逐个建立索引
            d[e->id] = e;  // 记录 id 到员工指针的映射
        }
        function<int(int)> dfs = [&](int i) -> int {  // 标准库 std::function 包装递归 lambda（自身递归必须先声明类型）
            int s = d[i]->importance;  // 当前员工的自身重要度
            for (int j : d[i]->subordinates) {  // 遍历该员工的所有直接下属 id
                s += dfs(j);  // 递归累加下属团队的重要度
            }
            return s;  // 返回「自身 + 全部下属」的重要度之和
        };  // 递归 lambda 定义结束
        return dfs(id);  // 从给定 id 开始计算整个团队的重要度
    }
};