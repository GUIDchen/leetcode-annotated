// 3408. 设计任务管理器 / Design Task Manager
// 核心思路：哈希表记录 taskId -> (userId, priority)，有序集合按 (-priority, -taskId) 维护执行顺序。
// 复杂度：add/edit/rmv/execTop 均为 O(log n)，空间复杂度 O(n)。
class TaskManager {  // 任务管理器类定义
private:  // 私有成员
    unordered_map<int, pair<int, int>> d;  // taskId -> (userId, priority) 的映射
    set<pair<int, int>> st;  // 按 (-priority, -taskId) 排序的有序集合

public:  // 公有接口
    TaskManager(vector<vector<int>>& tasks) {  // 构造函数：用初始任务列表初始化
        for (const auto& task : tasks) {  // 逐个加入任务
            add(task[0], task[1], task[2]);  // 复用 add 完成插入
        }  // 结束循环
    }  // 结束构造函数

    void add(int userId, int taskId, int priority) {  // 新增任务
        d[taskId] = {userId, priority};  // 记录任务所属用户与优先级
        st.insert({-priority, -taskId});  // 负号使集合按优先级、任务号从大到小排序
    }  // 结束 add

    void edit(int taskId, int newPriority) {  // 修改任务优先级
        auto [userId, priority] = d[taskId];  // 取出该任务的用户与旧优先级
        st.erase({-priority, -taskId});  // 删除旧优先级对应的条目
        st.insert({-newPriority, -taskId});  // 插入新优先级的条目
        d[taskId] = {userId, newPriority};  // 更新映射中的优先级
    }  // 结束 edit

    void rmv(int taskId) {  // 删除任务
        auto [userId, priority] = d[taskId];  // 取出该任务的用户与优先级
        st.erase({-priority, -taskId});  // 从有序集合中移除对应条目
        d.erase(taskId);  // 从映射中删除该任务
    }  // 结束 rmv

    int execTop() {  // 执行优先级最高的任务并返回其所属用户
        if (st.empty()) {  // 没有待执行任务
            return -1;  // 返回 -1
        }  // 结束空判断
        auto e = *st.begin();  // 取集合中优先级最高（同优先级取 taskId 最大）的条目
        st.erase(st.begin());  // 从集合中移除该条目
        int taskId = -e.second;  // 由负号还原任务号
        int userId = d[taskId].first;  // 查出任务所属用户
        d.erase(taskId);  // 从映射中删除已执行任务
        return userId;  // 返回执行者用户号
    }  // 结束 execTop
};  // 结束任务管理器类

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */
