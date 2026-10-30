# 3408. 设计任务管理器 / Design Task Manager
# 核心思路：哈希表记录 taskId -> (userId, priority)，有序列表按 (-priority, -taskId) 维护执行顺序。
# 复杂度：add/edit/rmv/execTop 均为 O(log n)，空间复杂度 O(n)。
class TaskManager:  # 任务管理器类定义
    def __init__(self, tasks: List[List[int]]):  # 构造函数：用初始任务列表初始化
        self.d = {}  # taskId -> (userId, priority) 的映射
        self.st = SortedList()  # 按 (-priority, -taskId) 排序的有序列表
        for task in tasks:  # 逐个加入任务
            self.add(*task)  # 解包三元组后复用 add

    def add(self, userId: int, taskId: int, priority: int) -> None:  # 新增任务
        self.d[taskId] = (userId, priority)  # 记录任务所属用户与优先级
        self.st.add((-priority, -taskId))  # 负号使排序按优先级、任务号从大到小

    def edit(self, taskId: int, newPriority: int) -> None:  # 修改任务优先级
        userId, priority = self.d[taskId]  # 取出用户与旧优先级
        self.st.discard((-priority, -taskId))  # 移除旧优先级条目
        self.d[taskId] = (userId, newPriority)  # 更新映射中的优先级
        self.st.add((-newPriority, -taskId))  # 插入新优先级条目

    def rmv(self, taskId: int) -> None:  # 删除任务
        _, priority = self.d[taskId]  # 取出旧优先级
        self.d.pop(taskId)  # 从映射中删除该任务
        self.st.remove((-priority, -taskId))  # 从有序列表中移除对应条目

    def execTop(self) -> int:  # 执行优先级最高的任务并返回其所属用户
        if not self.st:  # 没有待执行任务
            return -1  # 返回 -1
        taskId = -self.st.pop(0)[1]  # 弹出优先级最高（taskId 最大）的条目并还原任务号
        userId, _ = self.d[taskId]  # 查出任务所属用户
        self.d.pop(taskId)  # 从映射中删除已执行任务
        return userId  # 返回执行者用户号


# Your TaskManager object will be instantiated and called as such:
# obj = TaskManager(tasks)
# obj.add(userId,taskId,priority)
# obj.edit(taskId,newPriority)
# obj.rmv(taskId)
# param_4 = obj.execTop()
